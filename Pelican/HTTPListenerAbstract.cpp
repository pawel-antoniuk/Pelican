#include "HTTPListenerAbstract.h"

#include "IMetadata.h"
#include "Data.h"
#include "RequestParser.h"
#include "_GetRequestImpl.h"
#include "_PostRequestImpl.h"

void HTTPListenerAbstract::on_connection(IClient* client){
	client->set_metadata(new SingleData<std::string>());
}

void HTTPListenerAbstract::on_disconnection(IClient* client){
	delete client->get_metadata();
}

void HTTPListenerAbstract::on_read(IClient* client){
	auto data = client->recv(client->available());
	auto meta = dynamic_cast<SingleData<std::string>*>(client->get_metadata());
	meta->data += data;

	if (meta->data.length() > 4 && !meta->data.compare(meta->data.length() - 4, 4, "\r\n\r\n")){
		IRequest* request = RequestParser::parse(meta->data);
		IResponse* response;

		if (auto get_request = dynamic_cast<_GetRequestImpl*>(request))
			response = on_get_request(get_request);
		else if (auto post_request = dynamic_cast<_PostRequestImpl*>(request))
			response = on_post_request(post_request);
		else
			response = 0;


		client->send(response->data());

		meta->data = "";
		delete request;
		delete response;
	}
}