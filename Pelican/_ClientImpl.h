#pragma once
#include "IClient.h"
#include "IP.h"

#include <WinSock2.h>
#include <thread>

class _ClientImpl :	
	public virtual IClient{
public:
	_ClientImpl();
	_ClientImpl(SOCKET socket);
	_ClientImpl(const IP& ip);
	~_ClientImpl();

	virtual void send(const std::string& data) override;
	virtual std::string recv(int bufferSize) override;
	virtual void connect(const IP&) override;
	virtual void close() override;

	virtual IP addr() override;
	virtual int available() override;
	virtual unsigned long long id() override;

	virtual void set_metadata(IMetadata*) override;
	virtual IMetadata* get_metadata() override;
	virtual bool active() override;

	//listener thread only
	SOCKET _socket;

private:
	IMetadata* _metadata;
	bool _active;
};