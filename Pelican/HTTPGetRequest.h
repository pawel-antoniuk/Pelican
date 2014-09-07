#pragma once
#include "IPipeElement.h"
#include "ReqestEventCallerAbstract.h"

class HTTPGetRequest :
	public IPipeElement,
	public ReqestEventCallerAbstract{
public:
	HTTPGetRequest();
	HTTPGetRequest(RequestEventCallback);

private:
	virtual bool on_message(const std::string&, IMessageSender*, IMetadata*) override;
};

