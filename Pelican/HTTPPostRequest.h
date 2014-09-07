#pragma once
#include "IPipeElement.h"
#include "ReqestEventCallerAbstract.h"

class HTTPPostRequest : 
	public IPipeElement,
	public ReqestEventCallerAbstract{
public:
	HTTPPostRequest();
	HTTPPostRequest(RequestEventCallback);

private:
	virtual bool on_message(const std::string&, IMessageSender*, IMetadata*) override;
};

