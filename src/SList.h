#ifndef CLASS_SLIST_DEFINED_H
#define CLASS_SLIST_DEFINED_H

#include <initializer_list>
#include <ostream>

class SList
{
	using T = int;

	struct Block
	{
		T Value;
		Block* Next;

		Block(T value);
	};

	Block* Head;
	int Size;

public:
	class Iterator
	{
		friend class SList;
		Block* Current;
		Iterator(Block* block);

	public:
		Iterator& operator++();
		Iterator operator++(int);

		T& operator*() const;

		bool operator==(const Iterator& it) const;
		bool operator!=(const Iterator& it) const;
	};
	
	SList();
	SList(const std::initializer_list<T>& list);
	~SList();

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
	
	bool operator==(const SList& slist) const;
	bool operator!=(const SList& slist) const;
	
	bool operator<(const SList& slist) const;
	bool operator>(const SList& slist) const;
	
	bool operator<=(const SList& slist) const;
	bool operator>=(const SList& slist) const;
};

std::ostream& operator<<(std::ostream& out, const SList& slist);

#endif