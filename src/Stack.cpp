#include <iostream>
#include "Stack.h"
#include "quick_sort.h"
using namespace std;
Stack::Stack()
{
	data = nullptr;
	size = 0;
}
Stack::~Stack()
{
	if (data == nullptr) {
		delete[] data;
		size = 0;
	}
}
void Stack::push(int number)
{
	if (size % constant == 0) {
		int* updated_data = new int[size + constant];
		for (int i = 0; i < size; i++)
			updated_data[i] = data[i];
		if (data != nullptr)
			delete[] data;
		data = updated_data;
	}
	data[size++] = number;
}
void Stack::pop()
{
	if (size == 0)
		cout << "stack is not founded";
	if (--size % constant == 0) {
		int* updated_data = new int[size];
		for (int i = 0; i < size; i++)
			updated_data[i] = data[i];
		delete[] data;
		data = updated_data;
	}
}
int& Stack::peek()
{
	if (size == 0)
		cout << "stack is not founded";
	return data[size - 1];
}
int Stack::count()
{
	return size;
}
double Stack::get_average()
{
	if (size == 0)
		cout << "vector is not founded";
	double value = 0;
	for (int i = 0; i < size; i++)
		value += data[i];
	value = value / size;
	return value;
}
Stack Stack::concat_sort(const Stack& stack)
{
	Stack new_stack;

	new_stack.size = size + stack.size;
	new_stack.data = new int[new_stack.size];
	int current = 0;

	for (int i = 0; i < size; i++)
		new_stack.data[current++] = data[i];

	for (int i = 0; i < stack.size; i++)
		new_stack.data[current++] = stack.data[i];

	QuickSort(new_stack.data, new_stack.size);

	return new_stack;
}

bool Stack::operator == (const Stack& stack)
{
	if (this == &stack)
		return true;
	if (size != stack.size)
		return false;
	for (int i = 0; i < size; i++)
		if (data[i] != stack.data[i])
			return false;
	return true;
}
bool Stack::operator != (const Stack& stack)
{
	return !(*this == stack);
}
bool Stack::operator < (const Stack& stack)
{
	if (this == &stack)
		return false;
	int iterations_count = (size < stack.size) ? size : stack.size;
	for (int i = 0; i < iterations_count; i++)
		if (data[i] != stack.data[i])
			return data[i] < stack.data[i];
	return size < stack.size;
}
bool Stack::operator <= (const Stack& stack)
{
	return (*this < stack) || (*this == stack);
}
bool Stack::operator > (const Stack& stack)
{
	return !(*this < stack) && (*this != stack);
}
bool Stack::operator >= (const Stack& stack)
{
	return (*this > stack) || (*this == stack);
}

std::ostream& operator << (std::ostream& stream, const Stack& stack)
{
	if (stack.size == 0) {
		stream << "stack is not founded\n";
		return stream;
	}
	for (int i = stack.size - 1; i >= 0; i--)
		stream << stack.data[i] << "\n";
	return stream;
}