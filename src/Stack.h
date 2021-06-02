#ifndef STACK_INCLUDED
#define STACK_INCLUDED
#include <ostream>
class Stack
{
private:
	int* data;
	int size;
	static constexpr int constant = 2048;
public:
	Stack();
	~Stack();
	void push(int number);
	void pop();
	int& peek();
	int count();
	double get_average();
	Stack concat_sort(const Stack& stack);
	bool operator == (const Stack& stack);
	bool operator != (const Stack& stack);
	bool operator < (const Stack& stack);
	bool operator <= (const Stack& stack);
	bool operator > (const Stack& stack);
	bool operator >= (const Stack& stack);
	friend std::ostream& operator << (std::ostream& stream, const Stack& stack);
};
#endif

