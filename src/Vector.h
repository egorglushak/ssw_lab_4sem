#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED
#include <ostream>

class Vector
{
private:
	int* data;
	int size;
	static constexpr int constant = 4096;

public:
	Vector();
	~Vector();
	void push(int number);
	void pop();
	Vector concat_sort(const Vector& vector);
	int& at(int index);
	int count();
	double get_overage();
	bool operator == (const Vector& vector);
	bool operator != (const Vector& vector);
	bool operator < (const Vector& vector);
	bool operator <= (const Vector& vector);
	bool operator > (const Vector& vector);
	bool operator >= (const Vector& vector);
	friend std::ostream& operator << (std::ostream& stream, const Vector& vector);
};

#endif