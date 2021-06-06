#include <chrono>
#include <forward_list>
#include <list>
#include <iostream>

using namespace std;

#include "SList.h"
#include "DList.h"
#include "CBuffer.h"

chrono::steady_clock::time_point current_time()
{
	return chrono::steady_clock::now();
}

long long elapsed_milliseconds(chrono::steady_clock::time_point point)
{
	return chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - point).count();
}

static const int TESTS_CNT = 5000000;

int main()
{
	cout << "Tests started...\n\n";
	cout << "------------------------------------------------------------------\n\n";
	
	forward_list<int> stl_slist;
	SList new_slist;

	auto begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		stl_slist.push_front(i);
	}

	cout << "stl single linked list push_front: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		new_slist.push_front(i);
	}

	cout << "new single linked list push_front: " << elapsed_milliseconds(begin) << " ms\n\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		stl_slist.insert_after(stl_slist.begin(), i);
	}

	cout << "stl single linked list insert_after: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		new_slist.insert(i, new_slist.begin());
	}

	cout << "new single linked list insert: " << elapsed_milliseconds(begin) << " ms\n\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		stl_slist.erase_after(stl_slist.begin());
	}

	cout << "stl single linked list erase_after: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		new_slist.erase(new_slist.begin());
	}

	cout << "new single linked list erase: " << elapsed_milliseconds(begin) << " ms\n\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		stl_slist.pop_front();
	}

	cout << "stl single linked list pop_front: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		new_slist.pop_front();
	}

	cout << "new single linked list pop_front: " << elapsed_milliseconds(begin) << " ms\n\n";
	cout << "------------------------------------------------------------------\n\n";


	list<int> stl_dlist;
	DList new_dlist;

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		stl_dlist.push_front(i);
	}

	cout << "stl double linked list push_front: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		new_dlist.push_front(i);
	}

	cout << "new double linked list push_front: " << elapsed_milliseconds(begin) << " ms\n\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		stl_dlist.push_back(i);
	}

	cout << "stl double linked list push_back: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		new_dlist.push_back(i);
	}

	cout << "new double linked list push_back: " << elapsed_milliseconds(begin) << " ms\n\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		stl_dlist.insert(stl_dlist.begin(), i);
	}

	cout << "stl double linked list insert: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		new_dlist.insert(i, new_dlist.begin());
	}

	cout << "new double linked list insert: " << elapsed_milliseconds(begin) << " ms\n\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		stl_dlist.erase(stl_dlist.begin());
	}

	cout << "stl double linked list erase: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		new_dlist.erase(new_dlist.begin());
	}

	cout << "new double linked list erase: " << elapsed_milliseconds(begin) << " ms\n\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		stl_dlist.pop_front();
	}

	cout << "stl double linked list pop_front: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		new_dlist.pop_front();
	}

	cout << "new double linked list pop_front: " << elapsed_milliseconds(begin) << " ms\n\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		stl_dlist.pop_back();
	}

	cout << "stl double linked list pop_back: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		new_dlist.pop_back();
	}

	cout << "new double linked list pop_back: " << elapsed_milliseconds(begin) << " ms\n\n";
	cout << "------------------------------------------------------------------\n\n";


	CBuffer buffer(TESTS_CNT / 2);

	begin = current_time();

	for (int i = 0; i < TESTS_CNT; i++)
	{
		buffer.push(i);
	}

	cout << "circular buffer push: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT / 4; i++)
	{
		buffer.pop();
	}

	cout << "circular buffer pop: " << elapsed_milliseconds(begin) << " ms\n\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT / 4; i++)
	{
		buffer.insert(i, buffer.begin() + 1);
	}

	cout << "circular buffer insert: " << elapsed_milliseconds(begin) << " ms\n";

	begin = current_time();

	for (int i = 0; i < TESTS_CNT / 4; i++)
	{
		buffer.erase(buffer.begin() + 1);
	}

	cout << "circular buffer erase: " << elapsed_milliseconds(begin) << " ms\n\n";
	cout << "------------------------------------------------------------------\n\n";
	
	return 0;
}