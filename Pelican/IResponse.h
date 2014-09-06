#pragma once
#include <vector>
#include <string>

class IResponse{
public:
	typedef std::pair<std::string, std::string> PropertiesPairType;
	typedef std::vector<PropertiesPairType> PropertiesArrayType;

	virtual ~IResponse() {}

	virtual std::string data() = 0;
	virtual PropertiesArrayType properties() = 0;
};