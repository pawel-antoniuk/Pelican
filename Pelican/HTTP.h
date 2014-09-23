#pragma once
#include "DefaultResponse.h"
#include "FileMapper.h"
#include "HTTPListenerAbstract.h"
#include "PipeListenerAbstract.h"
#include "HTTPGetRequest.h"
#include "HTTPPostRequest.h"
#include "HTTPBadRequest.h"
#include "HTTPServerConfigManager.h"
#include "XMLParser.h"
#include "HTTPPipeListenerAbstract.h"

namespace HTTPResult{
	const std::string OK = "HTTP/1.1 200 OK";
	const std::string NOT_FOUND = "HTTP/1.1 404 Not Found";
	const std::string BAD_REQUEST = "HTTP/1.1 400 Bad Request";
}