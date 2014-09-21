#include "_ServerImpl.h"


_ServerImpl::_ServerImpl(){
}

_ServerImpl::~_ServerImpl(){
	close();
}

void _ServerImpl::listen(const IP& ip){
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ip.addr();
	addr.sin_port = ip.port();

	_listener_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (::bind(_listener_socket, (sockaddr*) &addr, sizeof(addr)) == SOCKET_ERROR)
		throw WSAException();

	if (::listen(_listener_socket, SOMAXCONN) == SOCKET_ERROR)
		throw WSAException();

	_listener_event = WSACreateEvent();
	if (WSAEventSelect(_listener_socket, _listener_event, FD_ACCEPT) == SOCKET_ERROR)
		throw WSAException();

	_listener_proc();
}

void _ServerImpl::async_bind(IServerListener* listener){
	_server_listener = listener;
}

void _ServerImpl::close(){
	//kick all clients
	for (auto& clients_group : _clients){
		for (int i = 0; i < clients_group->unit.count; ++i){
			clients_group->unit.clients[i]->close();
			WSASetEvent(clients_group->unit.events[i]); //stimutale group listener
		}
	}

	//wait until all threads terminate
	//no clients = no threads
	while (_clients.size())
		std::this_thread::sleep_for(std::chrono::milliseconds(0));

	//stop listening
	WSASetEvent(_listener_event);
}

void _ServerImpl::each_client(void(*func)(IClient*)){
	for (auto& clients : _clients)
		for (int i = 0; i < clients->unit.count; ++i)
			func(clients->unit.clients[i]);
}

_ClientImpl* _ServerImpl::create_client(SOCKET new_socket){
	return new _ClientImpl(new_socket);
}

_ClientImpl* _ServerImpl::_accept(){
	SOCKET new_socket = ::accept(_listener_socket, 0, 0);

	if (new_socket == INVALID_SOCKET)
		throw WSAException();

	return create_client(new_socket);
}

void _ServerImpl::_add(_ClientImpl* client){
	HANDLE evnt = WSACreateEvent();
	if (WSAEventSelect(client->_socket, evnt, FD_READ | FD_CLOSE) == SOCKET_ERROR)
		throw WSAException();

	//find free group
	size_t index = -1;
	for (int i = 0; i < _clients.size(); ++i)
		if (_clients[i]->unit.count < MAX_SLOTS_PER_THREAD)
			index = i;

	std::lock_guard<std::mutex> locker(_socket_group_mutex); //critical section

	//if not, create new group 1/2
	bool new_group_created = false;
	if (index == -1){
		index = _clients.size();

		ClientsGroup* clients = new ClientsGroup;
		clients->unit.count = 0;

		_clients.push_back(clients);
		new_group_created = true;
	}

	//add to group
	_clients[index]->unit.clients[_clients[index]->unit.count] = client;
	_clients[index]->unit.events[_clients[index]->unit.count] = evnt;
	++_clients[index]->unit.count;
	WSASetEvent(_clients[index]->unit.events[0]); //update cliens list in thread

	//create new group 2/2
	if (new_group_created){
		_clients[index]->thread = std::move(std::thread(std::bind(std::mem_fn(
			&_ServerImpl::_clients_group_listen_proc), this, &_clients[index]->unit)));
		_clients[index]->thread.detach();
	}
}

void _ServerImpl::_listener_proc(){
	WSANETWORKEVENTS events;
	try{
		while (1){
			DWORD i = WSAWaitForMultipleEvents(1, &_listener_event, FALSE, WSA_INFINITE, FALSE);
			if (i == WSA_WAIT_FAILED)
				throw WSAException();

			if (WSAEnumNetworkEvents(_listener_socket, _listener_event, &events) == SOCKET_ERROR)
				throw WSAException();

			if (events.lNetworkEvents == FD_ACCEPT){
				_ClientImpl* client = _accept();
				if (_server_listener)
					_server_listener->on_connection(client);
				_add(client);
			}
			else
				break;
		}
	}
	catch (SocketException& e){
		_server_listener->on_exception(&e);
		close();
	}
}

void _ServerImpl::_clients_group_listen_proc(ClientsGroup::Unit* unit){
	WSANETWORKEVENTS events;
	try{
		while (1){
			DWORD i = WSAWaitForMultipleEvents((DWORD) unit->count, unit->events, FALSE, WSA_INFINITE, FALSE);
			if (i == WSA_WAIT_FAILED)
				throw WSAException();

			//TODO: bug: wylaczony socket nie w parametrze = exception
			/*if (WSAEnumNetworkEvents(unit->clients[i]->_socket, unit->events[i], &events) == SOCKET_ERROR)
				throw WSAException();*/

			WSAEnumNetworkEvents(unit->clients[i]->_socket, unit->events[i], &events);

			if (events.lNetworkEvents & FD_CLOSE || !unit->clients[i]->active()){
				if (_server_listener)
					_server_listener->on_disconnection(unit->clients[i]);
				if (!_kick(unit, i))
					break;
			}
			else if (events.lNetworkEvents & FD_READ)
				if (_server_listener)
					_server_listener->on_read(unit->clients[i]);
		}
	}
	catch (SocketException& e){
		_server_listener->on_exception(&e);
		close();
	}
}

void _ServerImpl::_remove_group(ClientsGroup::Unit* unit){
	for (int i = 0; i < _clients.size(); ++i){
		if (&_clients[i]->unit == unit){
			delete _clients[i];
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

bool _ServerImpl::_kick(ClientsGroup::Unit* unit, int index){
	std::lock_guard<std::mutex> locker(_socket_group_mutex);
	for (auto& clients : _clients)
		if (&clients->unit == unit){
			delete clients->unit.clients[index];
			CloseHandle(clients->unit.events[index]);

			for (int i = index + 1; i < unit->count; ++i){
				unit->clients[i - 1] = unit->clients[i];
				unit->events[i - 1] = unit->events[i];
			}

			if (--unit->count == 0){//if there is no other, delete unit and singal thread
				_remove_group(unit);
				return false;
			}

			break;
		}

	return true;
}