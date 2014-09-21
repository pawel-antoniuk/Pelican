#pragma once
#include <string>
#include "Node.h"

class XMLParser{
public:
	static Node* create_tree(const std::string& buf);
};

