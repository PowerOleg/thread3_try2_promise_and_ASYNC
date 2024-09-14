#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
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

std::vector<int> init_filled_vector(const int size)
{
	std::vector<int> vector;
	vector.reserve(size);
	for (int i = 0, j = size - 1; i < size; i++, j--)
	{
		vector.push_back(i);
	}
	print(vector, size);
	return vector;
}

//template<typename T>
void parallel_stream(std::vector<int>::iterator first, std::vector<int>::iterator last, /*T&&*/ std::function<int(int)> const& function, const int size)
{
	if (size <= 2)
	{
		std::transform(first, last, first, function);
	}
	else
	{
		int size1 = size / 2;
		int size2 = size - size1;
		auto iterator_half = std::next(first, size1);

		std::future<void> future = std::async(std::launch::async, parallel_stream, first, iterator_half, function, size1);
		future.get();
		parallel_stream(iterator_half, last, function, size2);
	}
}

//std::for_each(first, last, [](int n) {std::cout << n << " "; });
//auto p_lambda = std::make_unique<void()>(lambda);
int main(int argc, char** argv)
{
	const int size = 13;
	std::vector<int> vector = init_filled_vector(size);
	auto lambda = [](int n) { return n * n;	};
	std::function<int(int)> function(lambda);
	parallel_stream(vector.begin(), vector.end(), std::move(function), size);
	std::cout << "the resulting vector values: ";
	print(vector, size);
	return 0;
}