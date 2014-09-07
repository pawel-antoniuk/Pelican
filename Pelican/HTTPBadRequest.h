#pragma once
#include "IPipeElement.h"
#include "ReqestEventCallerAbstract.h"

class HTTPBadRequest :
	public IPipeElement,
	public ReqestEventCallerAbstract{
public:
	HTTPBadRequest();
	HTTPBadRequest(RequestEventCallback);

private:
	virtual bool on_message(const std::string&, IMessageSender*) override;
};

