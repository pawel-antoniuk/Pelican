#pragma once
#include "DefaultResponse.h"
#include "FileReader.h"
#include "HTTPListenerAbstract.h"
#include "PipeListenerAbstract.h"
#include "HTTPGetRequest.h"
#include "HTTPPostRequest.h"
#include "HTTPBadRequest.h"

#include <map>

std::map<std::string, std::string> mime{
		{ "html", "text/html" },
		{ "css", "text/css" },
		{ "js", "text/javascript" },
		{ "png", "image/png" },
		{ "gif", "image/gif" },
		{ "jpg", "image/jpeg" },
};

const std::string HTTP11_OK = "HTTP/1.1 200 OK";
const std::string HTTP11_NOT_FOUND = "HTTP/1.1 404 Not Found";
const std::string HTTP11_BAD_REQUEST = "HTTP/1.1 400 Bad Request";