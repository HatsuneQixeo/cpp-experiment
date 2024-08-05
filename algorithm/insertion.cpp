#include <iostream>
#include <algorithm>
#include <chrono>
#include <string>
#include <numeric>
#include <vector>
#include <list>

std::vector<int>	createUnsortedArray(const unsigned int size)
{
	std::vector<int>	vec(size);

	std::iota(vec.begin(), vec.end(), 0);
	for (unsigned int i = 0; i < size; i++)
		std::swap(vec[i], vec[rand() % size]);
	return (vec);
}

template <template <typename, typename> class Container, typename _Tp, typename _Alloc = std::allocator<_Tp> >
std::ostream	&operator<<(std::ostream &stream, const Container<_Tp, _Alloc> &container)
{
	typename Container<_Tp, _Alloc>::const_iterator	it = container.begin();

	if (it == container.end())
		return (stream);
	std::cout << *it;
	while (++it != container.end())
		std::cout << ' ' << *it;
	return (stream);
}

template <typename Iterator>
void	linearInsertion(const Iterator begin, const Iterator end)
{
	typedef typename Iterator::value_type	T;

	if (begin == end)
		return ;
	for (Iterator it = std::next(begin); it != end; it++)
	{
		const T		key = *it;

#if 0 /* Original */
		Iterator	insert = std::prev(it);

		while (insert != std::prev(begin) && *insert > key)
		{
			*std::next(insert) = *insert;
			--insert;
		}
		*std::next(insert) = key;
#else /* Less function call to iterator */
		Iterator	key_dest = it;

		while (key_dest != begin && *std::prev(key_dest) > key)
		{
			T	&shift_toward = *key_dest;

			shift_toward = *--key_dest;
		}
		*key_dest = key;
#endif
	}
}

template <typename Iterator, typename T>
Iterator	binarySearch(const Iterator begin, const Iterator end, const T target)
{
	Iterator	left = begin;
	Iterator	right = end - 1;

	while (left <= right)
	{
		const Iterator	mid = left + ((right - left) / 2);

		if (*mid < target)
			left = mid + 1;
		else if (*mid > target)
			right = mid - 1;
		else
			return (mid);
	}
	return (end);
}

template <typename Iterator, typename T>
static Iterator	insertBinarySearch(const Iterator begin, const Iterator end, const T target)
{
	Iterator	left = begin;
	Iterator	right = end - 1;

	while (left <= right)
	{
		const Iterator	mid = left + ((right - left) / 2);

		if (*mid < target)
			left = mid + 1;
		else if (*mid > target)
			right = mid - 1;
		else
			return (mid + 1);
	}
	return (left);
}

template <typename Iterator>
void	binaryInsertion(const Iterator begin, const Iterator end)
{
	typedef typename Iterator::value_type	T;

	if (begin == end)
		return ;
	for (Iterator it = std::next(begin); it != end; it++)
	{
		const T			key = std::move(*it);
		const Iterator	insert = insertBinarySearch(begin, it, key);
		Iterator		shift = it;

		if (insert == it)
			continue ;
		while (shift != insert)
		{
			T	&shift_toward = *shift;

			shift_toward = *--shift;
		}
		*insert = key;
	}
}

template <typename Iterator>
void	mergeSort(const Iterator begin, const Iterator end)
{
	const unsigned int	size = end - begin;
	const Iterator		mid = begin + (size / 2);

	if (size < 2)
		return ;
	mergeSort(begin, mid);
	mergeSort(mid, end);
	std::inplace_merge(begin, mid, end);
}

template<typename Iterator>
using SortingFunction = void(*)(Iterator, Iterator);

template <class Container>
void	showSortTime(Container container, const SortingFunction<typename Container::iterator> sort)
{
	const auto	start = std::chrono::high_resolution_clock::now();
	sort(container.begin(), container.end());
	const auto	end = std::chrono::high_resolution_clock::now();
	const double	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() * 0.001;

	if (!std::is_sorted(container.begin(), container.end()))
		std::cout << "Error: Not Sorted" << std::endl;
	else
		std::cout << "Time Taken: " << duration  << " ms" << std::endl;
}

int	main(void)
{
	std::vector<int>	src = createUnsortedArray(3000);

	srand(time(nullptr));
	// std::sort(src.begin(), src.end());
	// for (unsigned int i = 0; i < 100; i++)
	// {
	// 	const int	finding = src[rand() % src.size()];
	// 	const auto	it = binarySearch(src.begin(), src.end(), finding);

	// 	if (it == src.end())
	// 		std::cout << "Error: Could not find: " << finding << std::endl;
	// 	else if (finding != *it)
	// 		std::cout << "Error: Found " << *it << " while searching for " << finding << std::endl;
	// 	// else
	// 	// 	std::cout << "Found " << finding << " in " << it - src.begin() << std::endl;
	// }
	showSortTime(src, binaryInsertion);
	showSortTime(src, linearInsertion);
	showSortTime(src, mergeSort);
	showSortTime(src, std::sort);
	// showSortTime(src, linearInsertion);
	// showSortTime(std::list<int>(src.begin(), src.end()), linearInsertion);
	// showSortTime(src, std::sort);
}
