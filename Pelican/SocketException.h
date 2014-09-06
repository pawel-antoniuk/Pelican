#pragma once
#include "IClient.h"

#include <memory>
#include <string>

class SocketException{
public:
	virtual ~SocketException() {}
};
/*
class InternalException : public SocketException{
public:
	enum ClientErrorType{
		MAXSLOTS,
	} type;

	std::shared_ptr<IClient> client;
};*/

class WSAException : public SocketException{
public:
	WSAException();
	int code();
	std::string format();

private:
	int _code;
};