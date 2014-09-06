#include "SocketManager.h"
#include "DefaultResponse.h"
#include "FileReader.h"
#include "HTTPListenerAbstract.h"
#include "PipeListener.h"
#include "HTTPGetRequest.h"
#include "HTTPPostRequest.h"

#include <iostream>
#pragma comment(lib, "ws2_32")


class HTTPListenerImpl : public HTTPListenerAbstract{
public:
	IResponse* on_get_request(IGetRequest* request) override{
		auto target = request->get_target_location();
		std::string file = target == "/" ? "index.html" : target;


		return new DefaultResponse(FileReader::read("C:/pages/" + file), "text/html");
	}

	IResponse* on_post_request(IPostRequest* request) override{
		auto target = request->get_target_location();
		std::string file = target == "/" ? "index.html" : target;

		return new DefaultResponse(FileReader::read("C:/pages/" + file), "text/html");
	}

	void on_exception(SocketException* e) override{
		if (WSAException* _e = dynamic_cast<WSAException*>(e)){
			std::printf("WSA exception #%d: %s", _e->code(), _e->format().c_str());
		}
		else /*if (InternalException* _e = dynamic_cast<InternalException*>(e))*/{
			std::printf("Undefined exception\n");
		}
	}
};


int main(){
	SocketManager::init();

	HTTPListenerImpl listener;

	try{
		/*HTTPGetRequest getReqest([](IRequest* request)->IResponse*{
			auto target = request->get_target_location();
			std::string file = target == "/" ? "index.html" : target;
			std::string out = FileReader::read("C:/pages/" + file);
			if (out.length() == 0)
			out = "asdasdasd";
			return new DefaultResponse(out, "text/html; charset=utf-8");
			});
			HTTPPostRequest postReqest([](IRequest* request)->IResponse*{
			auto target = request->get_target_location();
			std::string file = target == "/" ? "index.html" : target;
			std::string out = FileReader::read("C:/pages/" + file);
			if (out.length() == 0)
			out = "asdasdasd";
			return new DefaultResponse(out, "text/html; charset=utf-8");
			});

			PipeListener pipeListener;
			pipeListener.install(&getReqest);
			pipeListener.install(&postReqest);*/

		auto server = SocketManager::TCP::create_server();
		
		server->async_bind(&listener);
		//server->async_bind(&pipeListener);
		server->listen(IP(80));
	}
	catch (SocketException& e){
		listener.on_exception(&e);
	}

	SocketManager::cleanup();
}