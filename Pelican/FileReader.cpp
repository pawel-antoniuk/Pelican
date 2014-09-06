#include "FileReader.h"

#undef UNICODE
#include <Windows.h>

std::string FileReader::read(std::string path){
	HANDLE hFile = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

	if (hFile == INVALID_HANDLE_VALUE)
		return std::string();

	HANDLE hMap = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, 0);
	void* ptr = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
	DWORD size = GetFileSize(hFile, 0);

	std::string out((char*) ptr, (size_t) size);

	UnmapViewOfFile(ptr);
	CloseHandle(hMap);
	CloseHandle(hFile);

	return out;
}