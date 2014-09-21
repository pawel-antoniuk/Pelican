#include "XMLParser.h"

Node* XMLParser::create_tree(const std::string & buf){
	const char* input_buf = buf.c_str();
	char work_buf[512];
	size_t index = 0;
	Node* current_node = new Node();

	while (index < buf.size()){
		if (input_buf[index] == '<'){
			size_t b_i;
			Node::Attribute* current_attrib = nullptr;

			++index;
			for (; isspace(input_buf[index]); ++index);
			for (b_i = 0; !isspace(input_buf[index]) && input_buf[index] != '>'; ++index, ++b_i)
				work_buf[b_i] = input_buf[index];
			if (work_buf[0] == '/')
				current_node = current_node->parent();
			else
				current_node = current_node->child(std::string(work_buf, b_i));

			b_i = 0;
			while (1){
				if (input_buf[index] == '>'){
					if (b_i > 0)
						current_attrib = current_node->attr(std::string(work_buf, b_i));

					++index;
					break;
				}
				else if (input_buf[index] == '='){
					if (b_i > 0)
						current_attrib = current_node->attr(std::string(work_buf, b_i));

					++index;
					for (; isspace(input_buf[index]); ++index);
					if (input_buf[index] == '\"'){
						++index;
						for (b_i = 0; input_buf[index] != '\"'; ++index, ++b_i)
							work_buf[b_i] = input_buf[index];
						current_attrib->value(std::string(work_buf, b_i));
						b_i = 0;
						++index;
					}
				}
				else if (isspace(input_buf[index])){
					if (b_i > 0)
						current_attrib = current_node->attr(std::string(work_buf, b_i));

					for (; isspace(input_buf[index]); ++index);
				}
				else{
					work_buf[b_i++] = input_buf[index++];
				}
			}
		}
		else if (!isspace(input_buf[index])){
			size_t i;

			for (i = 0; input_buf[index] != '<' && input_buf[index] != '\n'; ++i, ++index){
				work_buf[i] = input_buf[index];
			}

			current_node->attr("#")->value(std::string(work_buf, i));
		}
		else{
			for (; isspace(input_buf[index]); ++index);
		}
	}

	return current_node;
}
