#pragma once
#include <string>

class IMessageSender{
public:
	virtual void send(const std::string&) = 0;
};