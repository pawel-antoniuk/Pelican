#include "SocketManager.h"
#include "DefaultResponse.h"
#include "FileReader.h"
#include "HTTPListenerAbstract.h"
#include "PipeListener.h"
#include "HTTPGetRequest.h"
#include "HTTPPostRequest.h"

#include <iostream>
#include <map>
#pragma comment(lib, "ws2_32")

/*
class HTTPListenerImpl : public HTTPListenerAbstract{
public:
IResponse* on_get_request(IGetRequest* request) override{
auto target = request->get_target_location();
std::string file = target == "/" ? "index.html" : target;
std::string ext = file.substr(file.rfind('.') + 1);

return new DefaultResponse(FileReader::read("C:/pages/" + file), mime[ext]);
}

IResponse* on_post_request(IPostRequest* request) override{
std::cout << "error\n";
/*auto target = request->get_target_location();
std::string file = target == "/" ? "index.html" : target;

return new DefaultResponse(FileReader::read("C:/pages/" + file), "text/html");
return 0;
}

void on_exception(SocketException* e) override{
if (WSAException* _e = dynamic_cast<WSAException*>(e)){
std::printf("WSA exception #%d: %s", _e->code(), _e->format().c_str());
}
else /*if (InternalException* _e = dynamic_cast<InternalException*>(e)){
std::printf("Undefined exception\n");
}
}
};*/

int main(){
	static std::map<std::string, std::string> mime{
			{ "html", "text/html" },
			{ "css", "text/css" },
			{ "js", "text/javascript" },
			{ "png", "image/png" },
			{ "gif", "image/gif" },
			{ "jpg", "image/jpeg" },
	};

	try{
		SocketManager::init();

		HTTPGetRequest getReqest([](IRequest* request)->IResponse*{
			auto target = request->get_target_location();
			std::string file = target == "/" ? "index.html" : target;
			std::string ext = file.substr(file.rfind('.') + 1);

			return new DefaultResponse(FileReader::read("C:/pages/" + file), mime[ext]);
		});
		HTTPPostRequest postReqest([](IRequest* request)->IResponse*{
			std::cout << "error\n";

			return 0;
		});

		PipeListener pipeListener;
		pipeListener.install(&getReqest);
		pipeListener.install(&postReqest);

		auto server = SocketManager::TCP::create_server();
		server->async_bind(&pipeListener);
		server->listen(IP(80));

		SocketManager::cleanup();
	}
	catch (SocketException& e){
		if (WSAException* _e = dynamic_cast<WSAException*>(&e)){
			std::printf("WSA exception #%d: %s", _e->code(), _e->format().c_str());
		}
		else /*if (InternalException* _e = dynamic_cast<InternalException*>(e))*/{
			std::printf("Undefined exception\n");
		}
	}
}