#include "HTTPPipeListenerAbstract.h"

#include "IMetadata.h"

bool HTTPPipeListenerAbstract::before_request(const std::string& data, IMetadata*& meta){
	if (data.length() > 4 && !data.compare(data.length() - 4, 4, "\r\n\r\n")){
		auto _meta = new SingleData<std::string>();
		_meta->data = data.substr(0, data.find(' '));
		meta = _meta;

		return true;
	}
	else
		return false;
}