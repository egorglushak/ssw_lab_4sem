#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED
#include <ostream>

class Queue
{
private:
	int* data;
	int size;
	int begin_id;
	static constexpr int constant = 2048;
public:
	Queue();
	~Queue();
	void push(int number);
	void pop();
	int& peek();
	int count();
	double get_average();
	Queue concat_sort(const Queue& queue);
	bool operator == (const Queue& queue);
	bool operator != (const Queue& queue);
	bool operator < (const Queue& queue);
	bool operator <= (const Queue& queue);
	bool operator > (const Queue& queue);
	bool operator >= (const Queue& queue);
	friend std::ostream& operator << (std::ostream& stream, const Queue& queue);
};
#endif