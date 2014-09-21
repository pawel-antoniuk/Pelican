#include "IP.h"

#include <WS2tcpip.h>

IP::IP(int ipAddr, short port){
	_addr = ipAddr;
	_port = port;
}

IP::IP(const std::string& ipAddr, short port){
	set_addr(ipAddr);
	set_port(port);
}

IP::IP(short port){
	_addr = INADDR_ANY;
	set_port(port);
}

IP::IP(const IP& ip){
	_addr = ip._addr;
	_port = ip._port;
}

int IP::addr() const{
	return _addr;
}

unsigned short IP::port() const{
	return _port;
}

void IP::set_addr(const std::string& addr){
	inet_pton(AF_INET, addr.c_str(), &_addr);
}

void IP::set_port(short port){
	_port = htons(port);
}

std::string IP::to_string() const{
	std::string out(16, 0);
	inet_ntop(AF_INET, (void*)&_addr, &out[0], 16);
	return out;
}

unsigned long IP::to_long() const{
	return _addr; 
}
//Mistrzostwo http://pl.wikibooks.org/wiki/C/strtok