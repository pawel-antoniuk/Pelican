#include "HTTPPostRequest.h"

#include "_PostRequestImpl.h"

HTTPPostRequest::HTTPPostRequest(){
}

HTTPPostRequest::HTTPPostRequest(RequestEventCallback callback){
	bind(callback);
}

bool HTTPPostRequest::on_message(const std::string& data, IMessageSender* sender){
	char type[8];
	char buf[255];
	sscanf_s(data.c_str(), "%s %s HTTP/1.1\r\n", type, sizeof(type), buf, sizeof(buf));

	bool state = false;
	if (!strcmp(type, "POST")){
		IRequest* request = new _PostRequestImpl(buf);
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
