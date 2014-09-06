#include "RequestParser.h"

#include "_GetRequestImpl.h"
#include "_PostRequestImpl.h"

IRequest* RequestParser::parse(std::string str){
	char type[8];
	char buf[255];
	sscanf_s(str.c_str(), "%s %s HTTP/1.1\r\n", type, sizeof(type), buf, sizeof(buf));

	if (strcmp(type, "GET")){
		return new _GetRequestImpl(buf);
	}
	else if (strcmp(type, "POST")){
		return new _PostRequestImpl(buf);
	}
	else
		return 0; //bad request
}
