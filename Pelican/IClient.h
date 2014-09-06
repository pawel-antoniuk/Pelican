#pragma once
#include "IMessageSender.h"

#include <memory>
#include <string>

class IP;
class IMetadata;

class IClient : public IMessageSender{
public:
	virtual ~IClient() {}

	virtual std::string recv(int n) = 0;
	virtual void connect(const IP&) = 0;
	virtual void close() = 0;

	virtual IP addr() = 0;
	virtual int available() = 0;
	virtual unsigned long long id() = 0;

	virtual void set_metadata(IMetadata*) = 0;
	virtual IMetadata* get_metadata() = 0;
	virtual bool active() = 0;
};