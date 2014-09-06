#include "DefaultResponse.h"


DefaultResponse::DefaultResponse(std::string data, std::string type){
	_result = "HTTP/1.1 200 OK";
	_properties.push_back(PropertiesPairType("Content-Type", type));
	_properties.push_back(PropertiesPairType("Content-Length", std::to_string(data.size())));
	_data = data;
}

std::string DefaultResponse::data(){
	std::string out = _result + "\r\n";
	for (auto& v : _properties)
		out += v.first + ": " + v.second + "\r\n";
	out += "\r\n";
	out += _data;

	return out;
}

DefaultResponse::PropertiesArrayType DefaultResponse::properties(){
	return _properties;
}