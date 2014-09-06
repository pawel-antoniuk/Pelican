#pragma once
#include "IServerListener.h"
#include "IGetRequest.h"
#include "IPostRequest.h"
#include "IResponse.h"

class HTTPListenerAbstract :
	public IServerListener{
public:
	virtual IResponse* on_get_request(IGetRequest *) = 0;
	virtual IResponse* on_post_request(IPostRequest*) = 0;

private:
	void on_connection(IClient* client) override;

	void on_disconnection(IClient* client) override;
	void on_read(IClient* client) override;
};
