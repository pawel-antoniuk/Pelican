#pragma once
#include "IPostRequest.h"

class _PostRequestImpl :
	public IPostRequest{
public:
	_PostRequestImpl(std::string);

	virtual std::string get_target_location() override;

private:
	std::string _target_location;
};
