#include <iostream>
#include <vector>
#include <forward_list>
#include <list>
#include <sstream>
#include <iomanip>
#include <array>
#include <deque>
#include "SimpleClock.hpp"

typedef std::vector<int>	Vector;
typedef std::deque<int>		Deque;
typedef std::list<int>		List;
typedef MicroSeconds		MeasureUnit;

template <template <typename, typename> class Container, typename T>
std::ostream	&operator<<(std::ostream &stream, const Container<T, std::allocator<T> > &storage)
{
	for (typename Container<T, std::allocator<T> >::const_iterator it = storage.begin(); it != storage.end(); it++)
	{
		if (it != storage.begin())
			stream << ", ";
		stream << *it;
	}
	stream << std::endl;
	return (stream);
}

template <class Container>
Container	container_createRand(const unsigned int size, const unsigned int randMax = RAND_MAX)
{
	Container	container(size);

	for (unsigned int i = 0; i < size; i++)
		container[i] = rand() % (randMax + 1);
	return (container);
}

template <class Container>
Container	container_createAscend(const unsigned int size, const long start = 0, const unsigned int multiply = 1)
{
	Container	container(size);

	for (unsigned int i = 0; i < size; i++)
		container[i] = (start + i) * multiply;
	return (container);
}

template <typename Iterator>
void	MyQuick(Iterator start, Iterator end)
{
	if (end - start < 2)
		return ;

	Iterator	pivot = start;
	Iterator	left = start + 1;
	Iterator	right = end - 1;

	while (left <= right)
	{
		while (left <= right && *left <= *pivot)
			left++;
		while (left <= right && *right > *pivot)
			right--;
		if (left < right)
			std::swap(*left, *right);
	}
	std::swap(*pivot, *right);
	MyQuick<Iterator>(start, right);
	MyQuick<Iterator>(right + 1, end);
}

template <typename Iterator>
void	MyMerge(Iterator begin, Iterator end)
{
	if (end - begin < 2)
		return ;

	const Iterator	mid = begin + (end - begin) / 2;

	MyMerge<Iterator>(begin, mid);
	MyMerge<Iterator>(mid, end);
	std::inplace_merge(begin, mid, end);
}

/* Could not handle negative number */
template <typename Iterator>
void	MyRadix(const Iterator begin, const Iterator end)
{
	typedef std::array<std::vector<int>, 10>	Bucket;

	if (end - begin < 2)
		return ;
	Bucket		bucket;
	const int	max = *std::max_element(begin, end);

	for (unsigned int digit = 1; max / digit > 0; digit *= bucket.size())
	{
		for (Iterator it = begin; it != end; it++)
			bucket[(*it / digit) % bucket.size()].push_back(*it);
		Iterator	arr = begin;

		for (Bucket::iterator it = bucket.begin(); it != bucket.end(); it++)
		{
			std::copy(it->begin(), it->end(), arr);
			arr += it->size();
			it->clear();
		}
	}
}

template <typename Iterator>
void	BitRadix(const Iterator begin, const Iterator end)
{
	const unsigned int	base = 0b10;
	const unsigned int	size = end - begin;

	for (int bit = 0; bit < 32; bit++)
	{
		int		bucket[base][size];
		int		bucket_element_size[base] = {0};

		for (unsigned int i = 0; i < base; i++)
			bzero(bucket[i], size * sizeof(int));
		for (Iterator it = begin; it != end; it++)
		{
			int		bitval = (*it >> bit) & 1;

			bucket[bitval][bucket_element_size[bitval]] = *it;
			bucket_element_size[bitval]++;
		}

		Iterator	arr = begin;
		for (unsigned int i = 0; i < base; i++)
		{
			std::copy(bucket[i], bucket[i] + bucket_element_size[i], arr);
			arr += bucket_element_size[i];
		}
	}
}

/* Bit radix */
// template <typename Iterator>
// void	BitRadix(const Iterator begin, const Iterator end)
// {
// 	typedef std::array<std::vector<int>, 0b10>	Bucket;

// 	if (end - begin < 2)
// 		return ;
// 	Bucket		bucket;
// 	const int	max = *std::max_element(begin, end);

// 	for (unsigned int digit = 1; max / digit > 0; digit *= bucket.size())
// 	{

// 		for (Iterator it = begin; it != end; it++)
// 			bucket[(*it >> digit) % bucket.size()].push_back(*it);
// 		Iterator	arr = begin;

// 		for (Bucket::iterator it = bucket.begin(); it != bucket.end(); it++)
// 		{
// 			std::copy(it->begin(), it->end(), arr);
// 			arr += it->size();
// 			it->clear();
// 		}
// 	}
// }

template <typename Container>
double	testCycle(Container &container, void (*const ft_sort)(typename Container::iterator, typename Container::iterator))
{
	SimpleClock<MeasureUnit>	clock("Cycle");

	ft_sort(container.begin(), container.end());
	return (clock.elapsed());
}

template <typename Iterator>
struct SortFunc
{
	typedef void	(*func)(Iterator, Iterator);
};

template <typename Container>
double	myTest(Container &container, typename SortFunc<typename Container::iterator>::func ft_sort)
{
	SimpleClock<MeasureUnit>	clock("Cycle");

	ft_sort(container.begin(), container.end());
	return (clock.elapsed());
}

/* Does not compile */
// template <typename Container, template <typename Iterator> class Sort>
// double	myTest(Container &container, Sort<typename Container::iterator> ft_sort)
// {
// 	SimpleClock<MeasureUnit>	clock("Cycle");

// 	ft_sort(container.begin(), container.end());
// 	return (clock.elapsed());
// }

template <class Container>
void	test(const unsigned int timeLimit, const std::string &clockName, void (*const ft_sort)(typename Container::iterator, typename Container::iterator))
{
	for (unsigned int size = 5; size <= INT_MAX; size *= 2)
	{
#if 1
		Container	container = container_createAscend<Container>(size);
#else
		Container	container = container_createAscend<Container>(size, -long(size / 2));
#endif
		std::random_shuffle(container.begin(), container.end());
		std::cout << '\n' << "Size: " << size << std::endl;

		const double		time = testCycle(container, ft_sort);
		std::stringstream	message;

		std::cout << "Time: " << time << '/' << timeLimit << std::endl;
		if (!std::is_sorted(container.begin(), container.end()))
			message << "Not Sorted!: " << container;
		else if (time >= timeLimit)
			message << "[" << size << "] Timeout: " << time << '/' << timeLimit;
		else
			continue ;
		std::cout << "Result: {" << clockName << "}: " << message.str() << std::endl;
		break ;
	}
	// std::cerr << "Press enter to continue: ";
	// std::cin.get();
}

int	main(int argc, char **argv)
{
	const unsigned int	timeLimit = 60;

	test<Vector>(timeLimit, "VectorMerge", MyMerge<Vector::iterator>);
	test<Deque>(timeLimit, "DequeMerge", MyMerge<Deque::iterator>);
	std::cerr << std::endl;

	test<Vector>(timeLimit, "VectorBitRadix", BitRadix<Vector::iterator>);
	test<Deque>(timeLimit, "DequeBitRadix", BitRadix<Deque::iterator>);
	std::cerr << std::endl;

	test<Vector>(timeLimit, "VectorRadix", MyRadix<Vector::iterator>);
	test<Deque>(timeLimit, "DequeRadix", MyRadix<Deque::iterator>);
	std::cerr << std::endl;

	test<Vector>(timeLimit, "VectorQuick", MyQuick<Vector::iterator>);
	test<Deque>(timeLimit, "DequeQuick", MyQuick<Deque::iterator>);
	std::cerr << std::endl;

	test<Vector>(timeLimit, "VectorSort", std::sort<Vector::iterator>);
	test<Deque>(timeLimit, "DequeSort", std::sort<Deque::iterator>);
	std::cerr << std::endl;
	std::vector<int>	vec;
	myTest(vec, MyQuick);
	// test<Vector>(timeLimit, "VectorStable", std::stable_sort<Vector::iterator>);
	// test<Deque>(timeLimit, "DequeStable", std::stable_sort<Deque::iterator>);
	// std::cerr << std::endl;
}
