#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "SimpleClock.hpp"

# define PROFILE(code)	({\
	const std::chrono::steady_clock::time_point	__start__ = std::chrono::high_resolution_clock::now();\
	code;\
	const std::chrono::steady_clock::time_point	__end__ = std::chrono::high_resolution_clock::now();\
	std::chrono::duration_cast<std::chrono::microseconds>(__end__ - __start__).count();\
})

/* std::list is not faster because the search would take years
	On the other side, when sorting std::list with binary_insertion,
	creating a vector copy for sorting seems to substitude the performance penalty for having to sort std::list with this specific algorithm.

	There's no practical aspect of this since std::list::sort exist.
 */
template <typename FowardIterator>
void	list_binary_insertion(const FowardIterator begin, const FowardIterator end)
{
	typedef typename std::iterator_traits<FowardIterator>::value_type	T;
	typedef std::vector<T>	Container;

	Container	c;

	c.reserve(std::distance(begin, end));
	c.push_back(std::move(*begin));
	for (FowardIterator it = std::next(begin); it != end; ++it)
	{
		const T							&value = *it;
		typename Container::iterator	insert_pos;
		const long	time_search = PROFILE(insert_pos = std::lower_bound(c.begin(), c.end(), value));
		const long	time_insert = PROFILE(c.insert(insert_pos, std::move(value)));

		// std::cerr << time_search << " > " << time_insert << '\n';
	}
	std::move(c.begin(), c.end(), begin);
}

template <typename BidirectionalIterator>
void	binary_insertion(const BidirectionalIterator begin, const BidirectionalIterator end)
{
	typedef typename std::iterator_traits<BidirectionalIterator>::value_type	T;
	BidirectionalIterator	it = begin;

	while (++it != end)
	{
		const T	value = std::move(*it);
		const BidirectionalIterator insert_pos = std::upper_bound(begin, it, value);

		if (it == insert_pos)
			continue ;

		BidirectionalIterator	it_shift = it;
		while (it_shift != insert_pos)
		{
			const BidirectionalIterator	ele = it_shift--;
			*it_shift = std::move(*ele);
		}
		*insert_pos = std::move(value);
	}
}

template <class Container, class Func>
long	show_time(const Container &ref, const Func f)
{
	Container	sort(ref);
	const long	elapsed = PROFILE(f(sort.begin(), sort.end()));

	if (std::is_sorted(sort.begin(), sort.end()) == false)
		throw (std::logic_error("Not sorted"));
	return (elapsed);
}

int	main(void)
{
	std::vector<int>	vec(100000);

	for (int &e : vec)
		e = ::rand();
	{
		std::list<int>	lst_sort(vec.begin(), vec.end());

		std::cout << "std::list::sort(): " << PROFILE(lst_sort.sort()) / 1000<< '\n';
	}
	std::cout << "vec" << '\n';
	std::cout << ::show_time(vec, ::binary_insertion<std::vector<int>::iterator>) / 1000 << '\n';
	std::cout << ::show_time(vec, ::list_binary_insertion<std::vector<int>::iterator>) / 1000 << '\n';
	{
		std::list<int>		lst(vec.begin(), vec.end());

		std::cout << "lst" << '\n';
		std::cout << ::show_time(lst, ::binary_insertion<std::list<int>::iterator>) / 1000 << '\n';
		std::cout << ::show_time(lst, ::list_binary_insertion<std::list<int>::iterator>) / 1000 << '\n';
	}
}
