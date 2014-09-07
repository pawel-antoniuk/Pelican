#include "SocketManager.h"
#include "HTTP.h"

#include <iostream>
#pragma comment(lib, "ws2_32")

//config
const std::string home_directory = "C:/pages/";
const std::string home_page = "index.html";
const std::string page_404 = "C:/pages/404.html";
const std::string page_400 = "C:/pages/400.html";

int main(){
	SocketManager::init();

	try{
		//http elements
		class : public PipeListenerAbstract{
		public:
			virtual bool on_pre_request(const std::string& data, IMetadata*& meta) override{
				if (data.length() > 4 && !data.compare(data.length() - 4, 4, "\r\n\r\n")){
					auto _meta = new SingleData<std::string>();
					_meta->data = data.substr(0, data.find(' '));
					meta = _meta;
					return true;
				}
				else return false;
			}

			virtual void on_exception(SocketException* e) override{
				if (WSAException* _e = dynamic_cast<WSAException*>(e)){
					std::printf("WSA exception #%d: %s", _e->code(), _e->format().c_str());
				}
				else /*if (InternalException* _e = dynamic_cast<InternalException*>(e))*/{
					std::printf("Undefined exception\n");
				}
			}
		}listener;

		HTTPGetRequest getReqest([](IRequest* request)->IResponse*{
			auto target = request->get_target_location();
			auto target_path = target == "/" ? home_page : target;
			auto ext = target_path.substr(target_path.rfind('.') + 1);
			auto context = FileReader::read(home_directory + target_path);

			if (context.size())	return new DefaultResponse(context, mime[ext], HTTP11_OK);
			else return new DefaultResponse(FileReader::read(page_404),
				mime["html"], HTTP11_NOT_FOUND);
		});

		HTTPPostRequest postReqest([](IRequest* request)->IResponse*{
			return 0;
		});

		HTTPBadRequest badRequest([](IRequest*)->IResponse*{
			return new DefaultResponse(FileReader::read(page_400),
				mime["html"], HTTP11_BAD_REQUEST);
		});

		listener.install(&getReqest);
		listener.install(&postReqest);
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
		else /*if (InternalException* _e = dynamic_cast<InternalException*>(e))*/{
			std::printf("Undefined exception\n");
		}
	}
	SocketManager::cleanup();
}