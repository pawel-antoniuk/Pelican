#include "_GetRequestImpl.h"

_GetRequestImpl::_GetRequestImpl(std::string target_location){
	_target_location = target_location;
}

std::string _GetRequestImpl::get_target_location(){
	return _target_location;
}