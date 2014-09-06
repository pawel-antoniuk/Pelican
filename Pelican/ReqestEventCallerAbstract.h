#pragma once
#include "IRequest.h"
#include "IResponse.h"

class ReqestEventCallerAbstract{
public:
	typedef IResponse*(*RequestEventCallback)(IRequest*);

	ReqestEventCallerAbstract() : 
		_callback(0){}

	virtual void bind(RequestEventCallback callback){
		_callback = callback;
	}

protected:
	IResponse* call(IRequest* request){
		return _callback(request);
	}

private:
	RequestEventCallback _callback;
};