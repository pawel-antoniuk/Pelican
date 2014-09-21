#include "_PostRequestImpl.h"

_PostRequestImpl::_PostRequestImpl(std::string target){
	_target_location = target;
}

std::string _PostRequestImpl::get_target_location(){
	return _target_location;
}

std::string _PostRequestImpl::get_target_extension(){
	return _target_location.substr(_target_location.rfind('.') + 1);
}
