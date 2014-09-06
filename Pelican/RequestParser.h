#pragma once
#include <string>

class IRequest;

class RequestParser{
public:
	static IRequest* parse(std::string);
};

