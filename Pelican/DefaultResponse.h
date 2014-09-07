#pragma once
#include "IResponse.h"

class DefaultResponse :
	public IResponse{
public:
	DefaultResponse(std::string, std::string mime, std::string result);

	virtual std::string data() override;
	virtual PropertiesArrayType properties() override;

private:
	std::string _result;
	std::string _data;
	PropertiesArrayType _properties;
};

