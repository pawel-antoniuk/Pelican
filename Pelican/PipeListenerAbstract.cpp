#include "PipeListenerAbstract.h"

#include "IPipeElement.h"
#include "IMetadata.h"
#include "IRequest.h"
#include "IResponse.h"
#include "RequestParser.h"

void PipeListenerAbstract::install(IPipeElement* element){
	_elements.push_back(element);
}

void PipeListenerAbstract::uninstall(IPipeElement* element){
	_elements.push_back(element);
}

void PipeListenerAbstract::on_connection(IClient* client){
	client->set_metadata(new SingleData<std::string>());
}

void PipeListenerAbstract::on_disconnection(IClient* client){
	delete client->get_metadata();
}

void PipeListenerAbstract::on_read(IClient* client){
	auto data = client->recv(client->available());
	auto meta = dynamic_cast<SingleData<std::string>*>(client->get_metadata());
	meta->data += data;

	IMetadata* metadata = nullptr;
	if (before_request(meta->data, metadata)){
		for (auto& element : _elements)
			if (element->on_message(meta->data, client, metadata))
				break;
		meta->data = "";
	}
	delete metadata;

	/*if (meta->data.length() > 4 && !meta->data.compare(meta->data.length() - 4, 4, "\r\n\r\n")){
		for (auto& element : _elements)
			if (element->on_message(meta->data, client))
				break;
		meta->data = "";
	}*/
}