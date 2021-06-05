#ifndef CLASS_DLIST_DEFINED_H
#define CLASS_DLIST_DEFINED_H

#include <initializer_list>
#include <ostream>

class DList
{
	using T = int;

	struct Block
	{
		T Value;
		
		Block* Prev;
		Block* Next;

		Block(T value);
	};

	Block* Head;
	Block* Tail;
	
	int Size;

public:
	class Iterator
	{
		friend class DList;
		
		Block* Current;
		Block** PrevField;
		
		Iterator(Block* block, Block** prev_field);

	public:
		Iterator& operator++();
		Iterator operator++(int);
		Iterator operator+(int offset) const;

		Iterator& operator--();
		Iterator operator--(int);
		Iterator operator-(int offset) const;
		
		T& operator*() const;

		bool operator==(const Iterator& it) const;
		bool operator!=(const Iterator& it) const;
	};

	DList();
	DList(const std::initializer_list<T>& list);
	~DList();

	void push_front(T value);
	void push_back(T value);

	void pop_front();
	void pop_back();

	void insert(T value, Iterator it);
	void erase(Iterator it);

	Iterator begin() const;
	Iterator end() const;

	int size() const;

	bool is_looped() const;
	Iterator find(T value) const;

	bool operator==(const DList& dlist) const;
	bool operator!=(const DList& dlist) const;

	bool operator<(const DList& dlist) const;
	bool operator>(const DList& dlist) const;

	bool operator<=(const DList& dlist) const;
	bool operator>=(const DList& dlist) const;
};

std::ostream& operator<<(std::ostream& out, const DList& dlist);

#endif