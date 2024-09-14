#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

template <typename T>
void print(const T array, const int size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

void set_min_in_promise(const int* array, const int i, const int size, std::promise<int> promise)
{
	int imin = i;
	for (size_t j = i + 1; j < size; j++)//code to find index of the min value
	{
		if (array[j] < array[imin])
		{
			imin = j;
		}
	}
	promise.set_value(imin);
}

void sort(int* dest_array, const std::vector<int> source, const int size)
{
	
	std::copy(source.begin(), source.end(), dest_array);

	for (size_t i = 0; i < size - 1; i++)
	{
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!THE START OF THE MAIN PART OF THE TASK
		std::promise<int> promise;
		std::future<int> future = promise.get_future();
		std::thread thread1(set_min_in_promise, dest_array, i, size, std::move(promise));
		thread1.detach();// if detach() thread1 will start when future.get(); if join() thread1 will finish before future.get()
		int imin = future.get();
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!THE END OF THE MAIN PART OF THE TASK 
		
		int a = dest_array[i];//just swap() between the min value element and the end element of the array
		dest_array[i] = dest_array[imin];
		dest_array[imin] = a;
	}
	
}

std::vector<int> init_filled_vector(const int n)
{
	std::vector<int> vector;//(n);
	vector.reserve(n);
	for (size_t i = 0, j = n - 1; i < n; i++, j--)//fill the array
	{
		vector.push_back(j);//vector[i] = j;
	}
	print(vector, n);
	return vector;
}
int main(int argc, char** argv)
{
	

	const int n = 20;
	std::vector<int> vector = init_filled_vector(n);
	int* array = new int[n];
	sort(array, vector, n);
	print(array, n);
	delete[] array;
	return 0;
}


