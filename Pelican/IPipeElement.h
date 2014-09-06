#pragma once
#include <string>
#include "IMessageSender.h"

class IPipeElement{
public:
	virtual ~IPipeElement() {}
	virtual bool on_message(const std::string&, IMessageSender*) = 0;
};