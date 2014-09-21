#pragma once
#include "PipeListenerAbstract.h"

class HTTPPipeListenerAbstract :
	public PipeListenerAbstract{
public:
	virtual bool before_request(const std::string& data, IMetadata*& meta) override;
};

