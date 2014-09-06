#pragma once
#include <string>

class IP{
public:
	IP() {}
	IP(int ipAddr, short port);
	IP(const std::string& ipAddr, short port);
	IP(short port);
	IP(const IP& ip){
		_addr = ip._addr;
		_port = ip._port;
	}

	int addr() const {
		return _addr;
	}

	unsigned short port() const {
		return _port;
	}

	std::string to_string();
	unsigned long to_long(){ return _addr; }

private:
	void set_addr(const std::string&);
	void set_port(short);

	unsigned long _addr;
	unsigned short _port;
};

