#pragma once
#include "IServerListener.h"
#include "IP.h"
#include "IClient.h"
#include "IServer.h"
#include "SocketException.h"
#include "_ClientImpl.h"

#include <WinSock2.h>
#include <vector>
#include <mutex>

#include "IServer.h"

const size_t MAX_SLOTS_PER_THREAD = 64;

struct ClientsGroup{
	std::thread thread;
	struct Unit{
		size_t count;
		_ClientImpl* clients[MAX_SLOTS_PER_THREAD];
		HANDLE events[MAX_SLOTS_PER_THREAD];
	} unit;
};

class _ServerImpl :
	public virtual IServer{
public:
	_ServerImpl();
	~_ServerImpl();

	virtual void listen(const IP& ip) override;
	virtual void async_bind(IServerListener* listener) override;
	virtual void close() override;
	virtual void each_client(void(*func)(IClient*)) override;
	virtual size_t slots() override;

protected:
	virtual _ClientImpl* create_client(SOCKET);

private:
	_ClientImpl* _accept();
	void _add(_ClientImpl*);
	void _listener_proc();
	void _clients_group_listen_proc(ClientsGroup::Unit*);
	void _remove_group(ClientsGroup::Unit*);
	bool _kick(ClientsGroup::Unit*, int index);

	IServerListener* _server_listener;

	SOCKET _listener_socket;
	HANDLE _listener_event;
	std::vector<ClientsGroup*> _clients;

	std::mutex _socket_group_mutex;
};

