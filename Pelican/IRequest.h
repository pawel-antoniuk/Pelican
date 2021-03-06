#pragma once
#include <string>

class IRequest{
public:
	virtual ~IRequest() {}

	virtual std::string get_target_location() = 0;
	virtual std::string get_target_extension() = 0;
};