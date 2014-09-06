#pragma once
#include "IResponse.h"

static const char* const MIME_HTML		 = "text/html";
static const char* const MIME_CSS		 = "text/css";
static const char* const MIME_JAVASCRIPT = "text/javascript";
static const char* const MIME_PLAIN		 = "text/plain";

class DefaultResponse :
	public IResponse{
public:
	DefaultResponse(std::string, std::string mime);

	virtual std::string data() override;
	virtual PropertiesArrayType properties() override;

private:
	std::string _result;
	std::string _data;
	PropertiesArrayType _properties;
};

