#include "SocketManager.h"
#include "_ServerImpl.h"

void SocketManager::init(){
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);
}

void SocketManager::cleanup(){
	WSACleanup();
}

std::shared_ptr<IClient> SocketManager::TCP::create_client(const IP& addr){
	return std::make_shared<_ClientImpl>(addr);
}

std::shared_ptr<IServer> SocketManager::TCP::create_server(){
	return std::make_shared<_ServerImpl>();
}