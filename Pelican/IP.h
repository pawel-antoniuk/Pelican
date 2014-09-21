#pragma once
#include <string>

class IP{
public:
	IP() {}
	IP(int ipAddr, short port);
	IP(const std::string& ipAddr, short port);
	IP(short port);
	IP(const IP& ip);

	int addr() const;
	unsigned short port() const;
	std::string to_string() const;
	unsigned long to_long() const;

private:
	void set_addr(const std::string&);
	void set_port(short);

	unsigned long _addr;
	unsigned short _port;
};

