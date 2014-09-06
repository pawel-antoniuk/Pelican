#pragma once
#include "IServerListener.h"

#include <vector>

class IPipeElement;

class PipeListener :
	public IServerListener
{
public:
	virtual void install(IPipeElement*);
	virtual void uninstall(IPipeElement*);

protected:
	virtual void on_connection(IClient* client) override;
	virtual void on_disconnection(IClient* client) override;
	virtual void on_read(IClient* client) override;
	virtual void on_exception(SocketException* error) override;
	
private:
	std::vector<IPipeElement*> _elements;
};

