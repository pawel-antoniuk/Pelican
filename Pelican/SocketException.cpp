#include "SocketException.h"

#include <Windows.h>

WSAException::WSAException(){
	_code = WSAGetLastError();
}

int WSAException::code(){
	return _code;
}

std::string WSAException::format(){
	LPVOID lpMsgBuf;
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, _code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR) &lpMsgBuf, 0, NULL);

	std::string str = (char*) lpMsgBuf;
	LocalFree(lpMsgBuf);

	return str;
}
