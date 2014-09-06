#pragma once

#include "SocketManager.h"
#include "IP.h"
#include "IServerListener.h"
#include "SocketException.h"
#include "IMetadata.h"

#include "IServer.h"
#include "IClient.h"

#include <memory>
#include <thread>

class IClient;
class IServer;
class IP;

class SocketManager{
public:
	static void init();
	static void cleanup();
	class TCP{
	public:
		static std::shared_ptr<IClient> create_client(const IP&);
		static std::shared_ptr<IServer> create_server();
	};
};

