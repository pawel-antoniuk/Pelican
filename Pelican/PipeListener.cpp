#include "PipeListener.h"

#include "IPipeElement.h"
#include "IMetadata.h"
#include "IRequest.h"
#include "IResponse.h"
#include "RequestParser.h"

void PipeListener::install(IPipeElement* element){
	_elements.push_back(element);
}

void PipeListener::uninstall(IPipeElement* element){
	_elements.push_back(element);
}

void PipeListener::on_connection(IClient* client){
	client->set_metadata(new SingleData<std::string>());
}

void PipeListener::on_disconnection(IClient* client){
	delete client->get_metadata();
}

void PipeListener::on_read(IClient* client){
	auto data = client->recv(client->available());
	auto meta = dynamic_cast<SingleData<std::string>*>(client->get_metadata());
	meta->data += data;

	if (meta->data.length() > 4 && !meta->data.compare(meta->data.length() - 4, 4, "\r\n\r\n")){
		for (auto& element : _elements)
			if (element->on_message(meta->data, client))
				break;
		meta->data = "";
	}
}

void PipeListener::on_exception(SocketException* error){
}
