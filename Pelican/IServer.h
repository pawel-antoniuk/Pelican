#pragma once
#include <memory>
#include <vector>
#include <thread>

class IP;
class IClient;
class IServerListener;

class IServer{
public:
	virtual ~IServer() {}

	virtual void listen(const IP&) = 0;
	virtual void async_bind(IServerListener*) = 0;
	virtual void close() = 0;
	virtual void each_client(void(*)(IClient*)) = 0;
	virtual size_t slots() = 0;
	//virtual std::vector<std::pair<SocketGroup, std::thread>> get_client_groups() = 0;
};

