#include "CBuffer.h"

CBuffer::CBuffer(int max_size)
{
	MaxSize = max_size;
}

CBuffer::CBuffer(const std::initializer_list<T>& init_list)
{
	MaxSize = init_list.size();

	for (auto value : init_list)
	{
		push(value);
	}
}

void CBuffer::push(T value)
{
	if (list.size() == MaxSize)
	{
		pop();
	}
	
	list.push_back(value);
}

void CBuffer::pop()
{
	list.pop_front();
}

void CBuffer::insert(T value, Iterator it)
{
	bool it_is_begin = it == begin();
	list.insert(value, it);

	if (list.size() > MaxSize)
	{
		if (it_is_begin)
			list.erase(begin() + 1);
		else
			list.pop_front();
	}
}

void CBuffer::erase(Iterator it)
{
	list.erase(it);
}

CBuffer::Iterator CBuffer::begin() const
{
	return list.begin();
}

CBuffer::Iterator CBuffer::end() const
{
	return list.end();
}

int CBuffer::size() const
{
	return list.size();
}

CBuffer::Iterator CBuffer::find(T value) const
{
	return list.find(value);
}

CBuffer::T& CBuffer::operator[](int index)
{
	if (index < 0 || index > list.size())
	{
		throw std::runtime_error("index out of range!");
	}
	
	Iterator it = begin();
	
	for (int i = 0; i < index; i++)
	{
		++it;
	}

	return *it;
}

bool CBuffer::operator==(const CBuffer& buffer) const
{
	return list == buffer.list;
}

bool CBuffer::operator!=(const CBuffer& buffer) const
{
	return list != buffer.list;
}

bool CBuffer::operator<(const CBuffer& buffer) const
{
	return list < buffer.list;
}

bool CBuffer::operator>(const CBuffer& buffer) const
{
	return list > buffer.list;
}

bool CBuffer::operator<=(const CBuffer& buffer) const
{
	return list <= buffer.list;
}

bool CBuffer::operator>=(const CBuffer& buffer) const
{
	return list >= buffer.list;
}


std::ostream& operator<<(std::ostream& out, const CBuffer& buffer)
{
	for (DList::Iterator it = buffer.begin(); it != buffer.end(); ++it)
	{
		out << *it << "\n";
	}

	return out;
}