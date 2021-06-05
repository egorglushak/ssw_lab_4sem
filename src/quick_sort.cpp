#include "quick_sort.h"
#include <utility>

void QuickSort(int* arr, int size)
{
	int& mid = arr[size / 2];

	int i = 0;
	int j = size - 1;

	do
	{
		while (arr[i] < mid)
			i++;

		while (arr[j] > mid)
			j--;

		if (i <= j)
			std::swap(arr[i++], arr[j--]);
	} while (i <= j);

	if (j > 0)
		QuickSort(arr, j + 1);

	if (i < size)
		QuickSort(arr + i, size - i);
}