#include <stdexcept>
#include "SList.h"

SList::Block::Block(T value)
{
	Value = value;
	Next = nullptr;
}

SList::Iterator::Iterator(Block* block)
{
	Current = block;
}

SList::Iterator& SList::Iterator::operator++()
{
	if (Current == nullptr)
	{
		throw std::runtime_error("pointer is empty!");
	}
	
	Current = Current->Next;
	return *this;
}

SList::Iterator SList::Iterator::operator++(int)
{
	if (Current == nullptr)
	{
		throw std::runtime_error("pointer is empty!");
	}
	
	Iterator it = *this;
	Current = Current->Next;
	return it;
}

SList::T& SList::Iterator::operator*() const
{
	if (Current == nullptr)
	{
		throw std::runtime_error("pointer is empty!");
	}
	
	return Current->Value;
}

bool SList::Iterator::operator==(const Iterator& it) const
{
	return Current == it.Current;
}

bool SList::Iterator::operator!=(const Iterator& it) const
{
	return Current != it.Current;
}

SList::SList()
{
	Head = nullptr;
	Size = 0;
}

SList::SList(const std::initializer_list<T>& list) : SList()
{
	for (auto value : list)
	{
		push_back(value);
	}
}

SList::~SList()
{
	while (Size != 0)
	{
		pop_front();
	}
}

void SList::push_front(T value)
{
	Block* new_head = new Block(value);
	Block* old_head = Head;

	Head = new_head;
	Head->Next = old_head;
	
	Size++;
}

void SList::push_back(T value)
{
	if (Size == 0)
	{
		push_front(value);
		return;
	}

	Block* block = Head;

	while (block->Next != nullptr)
	{
		block = block->Next;
	}

	block->Next = new Block(value);
	Size++;
}

void SList::pop_front()
{
	if (Size == 0)
	{
		throw std::runtime_error("list is empty!");
	}
	
	Block* old_head = Head;

	Head = Head->Next;
	delete old_head;
	Size--;
}

void SList::pop_back()
{
	if (Size == 0)
	{
		throw std::runtime_error("list is empty!");
	}
	
	if (Size == 1)
	{
		pop_front();
		return;
	}
	
	Block* block = Head;
	Block* prev_block = nullptr;

	while (block->Next != nullptr)
	{
		prev_block = block;
		block = block->Next;
	}

	delete block;
	prev_block->Next = nullptr;
	Size--;
}

void SList::insert(T value, Iterator it)
{
	if (it == begin())
	{
		push_front(value);
		return;
	}

	Block* block = new Block(value);
	Block* prev_block = Head;
	
	while (prev_block->Next != it.Current)
	{
		prev_block = prev_block->Next;
	}

	prev_block->Next = block;
	block->Next = it.Current;
	Size++;
}

void SList::erase(Iterator it)
{
	if (Size == 0)
	{
		throw std::runtime_error("list is empty!");
	}
	
	if (it == begin())
	{
		pop_front();
		return;
	}

	Block* prev_block = Head;

	while (prev_block->Next != it.Current)
	{
		prev_block = prev_block->Next;
	}

	prev_block->Next = it.Current->Next;
	delete it.Current;
	Size--;
}

SList::Iterator SList::begin() const
{
	return Head;
}

SList::Iterator SList::end() const
{
	return nullptr;
}

int SList::size() const
{
	return Size;
}

bool SList::is_looped() const
{
	int size = 0;

	for (Iterator it = begin(); it != end(); ++it)
	{
		if (++size > Size)
		{
			return true;
		}
	}

	return false;
}

SList::Iterator SList::find(T value) const
{
	Iterator it = begin();

	while (it != end() && *it != value)
	{
		++it;
	}
	
	return it;
}

bool SList::operator==(const SList& slist) const
{
	if (this == &slist)
	{
		return true;
	}

	if (Size != slist.Size)
	{
		return false;
	}

	Iterator first = begin();
	Iterator second = slist.begin();

	while (first != end())
	{
		if (*first++ != *second++)
		{
			return false;
		}
	}
	
	return true;
}

bool SList::operator!=(const SList& slist) const
{
	return !(*this == slist);
}

bool SList::operator<(const SList& slist) const
{
	if (this == &slist)
	{
		return false;
	}

	Iterator first = begin();
	Iterator second = slist.begin();

	while (first != end() && second != slist.end())
	{
		T first_value = *first++;
		T second_value = *first++;
		
		if (first_value != second_value)
		{
			return first_value < second_value;
		}
	}

	return Size < slist.Size;
}

bool SList::operator>(const SList& slist) const
{
	return !(*this < slist) && *this != slist;
}

bool SList::operator<=(const SList& slist) const
{
	return *this < slist && *this == slist;
}

bool SList::operator>=(const SList& slist) const
{
	return *this > slist && *this == slist;
}

std::ostream& operator<<(std::ostream& out, const SList& slist)
{
	for (SList::Iterator it = slist.begin(); it != slist.end(); ++it)
	{
		out << *it << "\n";
	}

	return out;
}