#include <iostream>
#include "Queue.h"
#include "quick_sort.h"
using namespace std;
Queue::Queue()
{
	begin_id = 0;
	data = nullptr;
	size = 0;
}
Queue::~Queue()
{
	if (data == nullptr) {
		delete[] data;
		size = 0;
	}
}
void Queue::push(int number)
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
void Queue::pop()
{
	if (size == 0)
		cout << "queue is not founded";
	begin_id++;
	size--;
	if (size % constant == 0 || begin_id % constant == 0) {
		int* updated_data = new int[size];
		for (int i = begin_id; i < begin_id + size; i++)
			updated_data[i - begin_id] = data[i];
		delete[] data;
		data = updated_data;
		begin_id = 0;
	}
}
int& Queue::peek()
{
	if (size == 0)
		cout << "queue is not founded";
	return data[size - 1];
}
int Queue::count()
{
	return size;
}
double Queue::get_average()
{
	if (size == 0)
		cout << "vector is not founded";
	double value = 0;
	for (int i = 0; i < size; i++)
		value += data[i];
	value = value / size;
	return value;
}
Queue Queue::concat_sort(const Queue& queue)
{
	Queue new_queue;

	new_queue.size = size + queue.size;
	new_queue.data = new int[new_queue.size];
	int current = 0;

	for (int i = begin_id; i < size + begin_id; i++)
		new_queue.data[current++] = data[i];

	for (int i = queue.begin_id; i < queue.size + queue.begin_id; i++)
		new_queue.data[current++] = queue.data[i];

	QuickSort(new_queue.data, new_queue.size);

	return new_queue;
}
bool Queue::operator == (const Queue& queue)
{
	if (this == &queue)
		return true;
	if (size != queue.size)
		return false;
	for (int i = 0; i < size; i++)
		if (data[i] != queue.data[i])
			return false;
	return true;
}
bool Queue::operator != (const Queue& queue)
{
	return !(*this == queue);
}
bool Queue::operator < (const Queue& queue)
{
	if (this == &queue)
		return false;
	int iterations_count = (size < queue.size) ? size : queue.size;
	for (int i = 0; i < iterations_count; i++)
		if (data[i] != queue.data[i])
			return data[i] < queue.data[i];
	return size < queue.size;
}
bool Queue::operator <= (const Queue& queue)
{
	return (*this < queue) || (*this == queue);
}
bool Queue::operator > (const Queue& queue)
{
	return !(*this < queue) && (*this != queue);
}
bool Queue::operator >= (const Queue& queue)
{
	return (*this > queue) || (*this == queue);
}
std::ostream& operator << (std::ostream& stream, const Queue& queue)
{
	if (queue.size == 0) {
		stream << "queue is not founded";
		return stream;
	}
	for (int i = queue.begin_id; i < queue.begin_id + queue.size; i++)
		stream << queue.data[i] << "\n";
	return stream;
}