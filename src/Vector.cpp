#include <iostream>
#include "Vector.h"
#include "quick_sort.h"
using namespace std;
Vector::Vector()
{
	data = nullptr;
	size = 0;
}
Vector::~Vector()
{
	if (data == nullptr) {
		delete[] data;
		size = 0;
	}
}
void Vector::push(int number)
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
void Vector::pop()
{
	if (size == 0)
		cout << "vector is not founded";
	if (--size % constant == 0) {
		int* updated_data = new int[size];
		for (int i = 0; i < size; i++)
			updated_data[i] = data[i];
		delete[] data;
		data = updated_data;
	}
}
Vector Vector::concat_sort(const Vector& vector)
{
	Vector new_vector;

	new_vector.size = size + vector.size;
	new_vector.data = new int[new_vector.size];
	int current = 0;

	for (int i = 0; i < size; i++)
		new_vector.data[current++] = data[i];

	for (int i = 0; i < vector.size; i++)
		new_vector.data[current++] = vector.data[i];

	QuickSort(new_vector.data, new_vector.size);

	return new_vector;
}
int& Vector::at(int index)
{
	if (size == 0)
		cout << "vector has not elemet";
	if (index < 0 || index > size - 1)
		cout << "error";
	return data[index];
}
int Vector::count()
{
	return size;
}
double Vector::get_overage()
{
	if (size == 0)
		cout << "vector is not founded";
	double value = 0;
	for (int i = 0; i < size; i++)
		value += data[i];
	value = value / size;
	return value;
}

bool Vector::operator == (const Vector& vector)
{
	if (this == &vector)
		return true;
	if (size != vector.size)
		return false;
	for (int i = 0; i < size; i++)
		if (data[i] != vector.data[i])
			return false;
	return true;
}
bool Vector::operator != (const Vector& vector)
{
	return !(*this == vector);
}
bool Vector::operator < (const Vector& vector)
{
	if (this == &vector)
		return false;
	int iterations_count = (size < vector.size) ? size : vector.size;
	for (int i = 0; i < iterations_count; i++)
		if (data[i] != vector.data[i])
			return data[i] < vector.data[i];
	return size < vector.size;
}
bool Vector::operator <= (const Vector& vector)
{
	return (*this < vector) || (*this == vector);
}
bool Vector::operator > (const Vector& vector)
{
	return !(*this < vector) && (*this != vector);
}
bool Vector::operator >= (const Vector& vector)
{
	return (*this > vector) || (*this == vector);
}
std::ostream& operator << (std::ostream& stream, const Vector& vector)
{
	if (vector.size == 0) {
		stream << "vector is not founded\n";
		return stream;
	}
	for (int i = 0; i < vector.size; i++)
		stream << vector.data[i] << "\n";
	return stream;
}
