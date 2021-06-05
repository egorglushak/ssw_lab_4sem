#ifndef CLASS_CBUFFER_DEFINED_H
#define CLASS_CBUFFER_DEFINED_H

#include "DList.h"

class CBuffer
{
	using T = int;

	DList list;
	int MaxSize;

public:
	using Iterator = DList::Iterator;

	CBuffer(int max_size);
	CBuffer(const std::initializer_list<T>& init_list);
	
	void push(T value);
	void pop();

	void insert(T value, Iterator it);
	void erase(Iterator it);

	Iterator begin() const;
	Iterator end() const;

	int size() const;
	Iterator find(T value) const;

	T& operator[](int index);
	
	bool operator==(const CBuffer& buffer) const;
	bool operator!=(const CBuffer& buffer) const;

	bool operator<(const CBuffer& buffer) const;
	bool operator>(const CBuffer& buffer) const;

	bool operator<=(const CBuffer& buffer) const;
	bool operator>=(const CBuffer& buffer) const;
};

std::ostream& operator<<(std::ostream& out, const CBuffer& buffer);

#endif