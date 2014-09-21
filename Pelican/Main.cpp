#include "SocketManager.h"
#include "HTTP.h"

#include <iostream>

#pragma comment(lib, "ws2_32")

HTTPServerConfigManager config("C:/pages/config.xml");
auto home_location = config.get_home_location();

int main(){
	SocketManager::init();

	try{
		class : public HTTPPipeListenerAbstract{
		public:
			virtual void on_exception(SocketException* e) override{
				if (WSAException* _e = dynamic_cast<WSAException*>(e)){
					std::printf("WSA exception #%d: %s", _e->code(), _e->format().c_str());
				}
				else{
					std::printf("Undefined exception\n");
				}
			}
		}listener;

		HTTPGetRequest getReqest([](IRequest* request)->IResponse*{
			auto target = request->get_target_location();

			if (target.length() > 0 && target[0] == '/')
				target = target.substr(1);
			if (target.length() == 0)
				target = config.get_page_path(200);

			auto context = FileReader::read(home_location + target);

			if (context.size()){
				return new DefaultResponse(context, config.get_mime(request->get_target_extension()), HTTPResult::OK);
			}
			else{
				return new DefaultResponse(FileReader::read(home_location + config.get_page_path(404)),
					config.get_mime("html"), HTTPResult::NOT_FOUND);
			}
		});

		HTTPBadRequest badRequest([](IRequest*)->IResponse*{
			return new DefaultResponse(FileReader::read(home_location + config.get_page_path(400)),
				config.get_mime("html"), HTTPResult::BAD_REQUEST);
		});

		listener.install(&getReqest);
		listener.install(&badRequest);

		//tcp server
		auto server = SocketManager::TCP::create_server();
		server->async_bind(&listener);
		server->listen(IP(80));
	}
	catch (SocketException& e){
		if (WSAException* _e = dynamic_cast<WSAException*>(&e)){
			std::printf("WSA exception #%d: %s", _e->code(), _e->format().c_str());
		}
		else{
			std::printf("Undefined exception\n");
		}
	}

	SocketManager::cleanup();
}