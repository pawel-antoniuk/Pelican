#pragma once
#include "IGetRequest.h"

class _GetRequestImpl :
	public IGetRequest{
public:
	_GetRequestImpl(std::string target_location);

	virtual std::string get_target_location() override;
	virtual std::string get_target_extension() override;

private:
	std::string _target_location;
};

