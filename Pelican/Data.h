#pragma once
#include <memory>

class Data{
public:
	typedef std::shared_ptr<const char> DataType;

	Data() : _ptr(nullptr), _size(0) {}
	Data(DataType ptr, size_t size) : _ptr(ptr), _size(size) {}

	void setPtr(DataType data){
		_ptr = data;
	}

	void setSize(size_t size){
		_size = size;
	}

	DataType getPtr() const{
		return _ptr;
	}

	size_t getSize() const{
		return _size;
	}

private:
	DataType _ptr;
	size_t _size;
};

