#pragma once
#include <string>
#include "IMessageSender.h"
#include "IMetadata.h"

class IPipeElement{
public:
	virtual ~IPipeElement() {}
	virtual bool on_message(const std::string&, IMessageSender*, IMetadata*) = 0;
};