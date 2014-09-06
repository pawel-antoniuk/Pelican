#pragma once
class IMetadata
{
public:
	virtual ~IMetadata() {}
};

template<typename T>
class SingleData : public IMetadata{
public:
	T data;
};
