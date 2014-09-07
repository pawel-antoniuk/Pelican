#pragma once
#include "IServerListener.h"

#include <vector>

class IPipeElement;

class PipeListenerAbstract :
	public IServerListener{
public:
	typedef bool(*PreRequestCallback)(const std::string&, IMetadata*&);

	virtual void install(IPipeElement*);
	virtual void uninstall(IPipeElement*);

protected:
	virtual bool on_pre_request(const std::string&, IMetadata*&) = 0;

	virtual void on_connection(IClient* client) override;
	virtual void on_disconnection(IClient* client) override;
	virtual void on_read(IClient* client) override;
	
private:
	std::vector<IPipeElement*> _elements;
};

