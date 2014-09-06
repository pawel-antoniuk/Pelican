#pragma once
#include "SocketException.h"

#include <memory>

class IServer;
class IClient;

class IServerListener{
public:
	virtual ~IServerListener() {}

	virtual void on_connection(IClient* client) = 0;
	virtual void on_disconnection(IClient* client) = 0;
	virtual void on_read(IClient* client) = 0;
	virtual void on_exception(SocketException* error) = 0;
};