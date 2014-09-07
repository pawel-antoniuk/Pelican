#include "HTTPGetRequest.h"

#include "_GetRequestImpl.h"

#include <iostream>

HTTPGetRequest::HTTPGetRequest(){
}

HTTPGetRequest::HTTPGetRequest(RequestEventCallback callback){
	bind(callback);
}

bool HTTPGetRequest::on_message(const std::string& data, IMessageSender* sender){
	char type[8];
	char buf[255];
	sscanf_s(data.c_str(), "%s %s HTTP/1.1\r\n", type, sizeof(type), buf, sizeof(buf));

	bool state = false;
	if (!strcmp(type, "GET")){
		IRequest* request = new _GetRequestImpl(buf);
		IResponse* response = call(request);
		if (response){
			sender->send(response->data());
			delete response;
			state = true;
		}
		delete request;
	}

	return state;
}
