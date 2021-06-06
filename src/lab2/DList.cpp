#include <stdexcept>
#include "DList.h"

DList::Block::Block(T value)
{
	Value = value;
	Prev = nullptr;
	Next = nullptr;
}

DList::Iterator::Iterator(Block* block, Block** prev_field = nullptr)
{
	Current = block;
	PrevField = prev_field;
}

DList::Iterator& DList::Iterator::operator++()
{
	if (Current == nullptr)
	{
		throw std::runtime_error("pointer is empty!");
	}

	Current = Current->Next;
	return *this;
}

DList::Iterator DList::Iterator::operator++(int)
{
	if (Current == nullptr)
	{
		throw std::runtime_error("pointer is empty!");
	}

	Iterator it = *this;
	Current = Current->Next;
	return it;
}

DList::Iterator DList::Iterator::operator+(int offset) const
{
	Iterator it = *this;

	for (int i = 0; i < offset; i++)
	{
		++it;
	}
	
	return it;
}

DList::Iterator& DList::Iterator::operator--()
{
	if (Current == nullptr && PrevField != nullptr)
	{
		*this = Iterator(*PrevField, nullptr);
		return *this;
	}
	
	if (Current == nullptr)
	{
		throw std::runtime_error("pointer is empty!");
	}

	Current = Current->Prev;
	return *this;
}

DList::Iterator DList::Iterator::operator--(int)
{
	if (Current == nullptr && PrevField != nullptr)
	{
		Block* temp = Current;
		*this = Iterator(*PrevField, nullptr);
		return Iterator(temp, nullptr);
	}

	if (Current == nullptr)
	{
		throw std::runtime_error("pointer is empty!");
	}

	Iterator it = *this;
	Current = Current->Prev;
	return it;
}

DList::Iterator DList::Iterator::operator-(int offset) const
{
	Iterator it = *this;

	for (int i = 0; i < offset; i++)
	{
		--it;
	}

	return it;
}

DList::T& DList::Iterator::operator*() const
{
	if (Current == nullptr)
	{
		throw std::runtime_error("pointer is empty!");
	}

	return Current->Value;
}

bool DList::Iterator::operator==(const Iterator& it) const
{
	return Current == it.Current;
}

bool DList::Iterator::operator!=(const Iterator& it) const
{
	return Current != it.Current;
}

DList::DList()
{
	Head = nullptr;
	Tail = nullptr;
	Size = 0;
}

DList::DList(const std::initializer_list<T>& list) : DList()
{
	for (auto value : list)
	{
		push_back(value);
	}
}

DList::~DList()
{
	while (Size != 0)
	{
		pop_front();
	}
}

void DList::push_front(T value)
{
	Block* old_head = Head;

	Head = new Block(value);
	Head->Next = old_head;

	if (old_head != nullptr)
	{
		old_head->Prev = Head;
	}

	if (++Size == 1)
	{
		Tail = Head;
	}
}

void DList::push_back(T value)
{
	if (Size == 0)
	{
		push_front(value);
		return;
	}

	Block* new_tail = new Block(value);
	Block* old_tail = Tail;

	Tail = new_tail;
	old_tail->Next = Tail;
	Tail->Prev = old_tail;

	Size++;
}

void DList::pop_front()
{
	if (Size == 0)
	{
		throw std::runtime_error("list is empty!");
	}

	Block* old_head = Head;
	Head = Head->Next;

	if (Head != nullptr)
	{
		Head->Prev = nullptr;
	}
	
	delete old_head;
	Size--;
}

void DList::pop_back()
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

	Block* old_tail = Tail;
	Tail = Tail->Prev;
	Tail->Next = nullptr;

	delete old_tail;
	Size--;
}

void DList::insert(T value, Iterator it)
{
	if (it == begin())
	{
		push_front(value);
		return;
	}
	
	if (it == end())
	{
		push_back(value);
		return;
	}

	Block* prev_block = it.Current->Prev;
	Block* new_block = new Block(value);

	prev_block->Next = new_block;
	new_block->Prev = prev_block;

	new_block->Next = it.Current;
	it.Current->Prev = new_block;
	
	Size++;
}

void DList::erase(Iterator it)
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

	if (it == end() - 1)
	{
		pop_back();
		return;
	}

	Block* prev_block = it.Current->Prev;
	Block* next_block = it.Current->Next;

	prev_block->Next = next_block;
	next_block->Prev = prev_block;
	
	delete it.Current;
	Size--;
}

DList::Iterator DList::begin() const
{
	return Iterator(Head);
}

DList::Iterator DList::end() const
{
	return Iterator(nullptr, const_cast<Block**>(&Tail));
}

int DList::size() const
{
	return Size;
}

bool DList::is_looped() const
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

DList::Iterator DList::find(T value) const
{
	Iterator it = begin();

	while (it != end() && *it != value)
	{
		++it;
	}

	return it;
}

bool DList::operator==(const DList& dlist) const
{
	if (this == &dlist)
	{
		return true;
	}

	if (Size != dlist.Size)
	{
		return false;
	}

	Iterator first = begin();
	Iterator second = dlist.begin();

	while (first != end())
	{
		if (*first++ != *second++)
		{
			return false;
		}
	}

	return true;
}

bool DList::operator!=(const DList& dlist) const
{
	return !(*this == dlist);
}

bool DList::operator<(const DList& dlist) const
{
	if (this == &dlist)
	{
		return false;
	}

	Iterator first = begin();
	Iterator second = dlist.begin();

	while (first != end() && second != dlist.end())
	{
		T first_value = *first++;
		T second_value = *first++;

		if (first_value != second_value)
		{
			return first_value < second_value;
		}
	}

	return Size < dlist.Size;
}

bool DList::operator>(const DList& dlist) const
{
	return !(*this < dlist) && *this != dlist;
}

bool DList::operator<=(const DList& dlist) const
{
	return *this < dlist && *this == dlist;
}

bool DList::operator>=(const DList& dlist) const
{
	return *this > dlist && *this == dlist;
}

std::ostream& operator<<(std::ostream& out, const DList& dlist)
{
	for (DList::Iterator it = dlist.begin(); it != dlist.end(); ++it)
	{
		out << *it << "\n";
	}

	return out;
}