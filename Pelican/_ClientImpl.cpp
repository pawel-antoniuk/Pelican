#include "_ClientImpl.h"

_ClientImpl::_ClientImpl() : _active(false) {}

_ClientImpl::_ClientImpl(SOCKET socket) : _socket(socket), _active(true) {}

_ClientImpl::_ClientImpl(const IP& ip) : _active(false) {
	connect(ip);
}

_ClientImpl::~_ClientImpl(){
	close();
}

void _ClientImpl::send(const std::string& data){
	int n = 0;
	while (n < data.size()) //send all
		n += ::send(_socket, &data.data()[n], data.size() - n, 0);
}

std::string _ClientImpl::recv(int bufferSize){
	char* buf = new char[bufferSize];
	int recived = ::recv(_socket, buf, bufferSize, 0);
	return std::string(buf, recived);
}

void _ClientImpl::connect(const IP& ip){
	if (!_active){
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = ip.port();
		addr.sin_addr.s_addr = ip.addr();
		_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		::connect(_socket, (sockaddr*) &addr, sizeof(addr));
		_active = true;
	}
}
#include <iostream>
void _ClientImpl::close(){
	if (_active){
		::shutdown(_socket, SD_BOTH);
		::closesocket(_socket);
		_active = false;
	}
}

IP _ClientImpl::addr(){
	sockaddr_in addr;
	int len = sizeof(addr);
	::getsockname(_socket, (sockaddr*) &addr, &len);
	return IP(addr.sin_addr.S_un.S_addr, ntohs(addr.sin_port));
}

int _ClientImpl::available(){
	u_long out;
	ioctlsocket(_socket, FIONREAD, &out);
	return out;
}

unsigned long long _ClientImpl::id(){
	return _socket;
}

void _ClientImpl::set_metadata(IMetadata* metadata){
	_metadata = metadata;
}

IMetadata* _ClientImpl::get_metadata(){
	return _metadata;
}

bool _ClientImpl::active(){
	return _active;
}