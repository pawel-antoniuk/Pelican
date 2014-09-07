#include "HTTPBadRequest.h"

HTTPBadRequest::HTTPBadRequest(){
}

HTTPBadRequest::HTTPBadRequest(RequestEventCallback callback){
	bind(callback);
}

bool HTTPBadRequest::on_message(const std::string& data, IMessageSender* sender, IMetadata*){
	IResponse* response = call(0);
	sender->send(response->data());
	delete response;
	return true;
}
