#pragma once
#include <string>
#include <map>
#include "Node.h"

class HTTPServerConfigManager{
public:
	HTTPServerConfigManager();
	HTTPServerConfigManager(const std::string& path);
	~HTTPServerConfigManager();

	void load_config(const std::string& path);
	const std::string& get_page_path(int code);
	const std::string& get_mime(const std::string& ext);
	const std::string& get_home_location();

private:
	Node* root;
};

