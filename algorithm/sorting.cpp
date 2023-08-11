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

template <typename Iterator>
void	printRange(const std::string &name, const Iterator start, const Iterator end)
{
	std::cout << name << ": ";
	if (start == end)
		std::cout << "empty" << std::endl;
	else
	{
		for (Iterator it = start; it != end - 1; it++)
			std::cout << *it << ", ";
		std::cout << *(end - 1) << std::endl;
	}
}

template <typename Iterator>
void	MyInsertion(Iterator start, Iterator end)
{
	typedef typename std::iterator_traits<Iterator>::value_type	T;

	for (Iterator element = start + 1; element != end; element++)
	{
		Iterator	it_insert = element;
		T			insert = *it_insert;

		while (it_insert != start && *(it_insert - 1) > insert)
		{
			*it_insert = *(it_insert - 1);
			it_insert--;
		}
		*it_insert = insert;
	}
}

#define TIM_INSERT 0x10

template <typename Iterator>
void	TimSort(const Iterator begin, const Iterator end)
{
	const ptrdiff_t	size = std::distance(begin, end);

	if (size < 2)
		return ;
	else if (size < TIM_INSERT)
		MyInsertion(begin, end);
	else
	{
		const Iterator	mid = begin + (size / 2);

		TimSort(begin, mid);
		TimSort(mid, end);
		std::inplace_merge(begin, mid, end);
	}
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

template <class Container>
void	templateSort(Container &arr, void (*const ft_sort)(typename Container::iterator, typename Container::iterator))
{
	ft_sort(arr.begin(), arr.end());
}

template <class Container>
void	testTimeSort(const Container &source)
{
	{
		Container					container(source.begin(), source.end());
		SimpleClock<MilliSeconds>	clock("Std::sort");
		templateSort<Container>(container, std::sort);
	}
	{
		Container					container(source.begin(), source.end());
		SimpleClock<MilliSeconds>	clock("std::__insertion_sort");
		templateSort<Container>(container, std::__insertion_sort);
	}
}

template <typename Iterator>
void	heapsort(Iterator start, Iterator end)
{
	std::make_heap(start, end);
	std::sort_heap(start, end);
}

template <typename Iterator>
void	MyQuick(const Iterator start, const Iterator end)
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

/* Could not handle negative */
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
void	bitwiseradixsort(const Iterator begin, const Iterator end)
{
	// typedef std::array<std::vector<int>, 0b10>	Bucket;
	const unsigned int	base = 0b10;
	const unsigned int	size = end - begin;

	for (int bit = 0; bit < (sizeof(int) * 8); bit++)
	{
		// std::cout << "bit: " << pow(2,  bit) << std::endl;
		// std::cout << "bit: " << (1 << bit) << std::endl;
		int		bucket[base][size];
		int		bucket_element_size[base] = {0};

		for (unsigned int i = 0; i < base; i++)
			bzero(bucket[i], size * sizeof(int));
		// for (unsigned int i = 0; i < base; i++)
			// std::cout << "bucket[" << i << "]: " << bucket_element_size[i] << std::endl;
		for (Iterator it = begin; it != end; it++)
		{
			int		bitval = (*it >> bit) & 1;

			bucket[bitval][bucket_element_size[bitval]] = *it;
			bucket_element_size[bitval]++;
		}
		// for (unsigned int i = 0; i < base; i++)
		// {
		// 	std::cout << "bucket[" << i << "]: ";
		// 	std::cout << "size: " << bucket_element_size[i] << " ";
		// 	std::cout << "content: ";
		// 	for (int j = 0; j < bucket_element_size[i]; j++)
		// 		std::cout << bucket[i][j] << " ";
		// 	std::cout << std::endl;
		// }
		// std::cout << std::endl;
		// std::cin.get();

		Iterator	arr = begin;
		for (unsigned int i = 0; i < base; i++)
		{
			std::copy(bucket[i], bucket[i] + bucket_element_size[i], arr);
			arr += bucket_element_size[i];
		}
	}
}

// void	bitwiseradixsort(int *arr, int size)
// {
// 	int		bucket[2][size];
// 	int		*in = arr;
// 	int		*out = bucket[1];
// 	int		bit = 0;

// 	while (bit < 32)
// 	{
// 		int		bucket_index = 0;

// 		for (int i = 0; i < size; i++)
// 		{
// 			int		bitval = (in[i] >> bit) & 1;

// 			bucket[bitval][bucket_index] = in[i];
// 			bucket_index += bitval;
// 		}
// 		out = bucket[bucket_index == size];
// 		bit++;
// 	}
// 	std::copy(out, out + size, arr);
// }

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

template <class Container>
void	test(const unsigned int timeLimit, const std::string &clockName, void (*const ft_sort)(typename Container::iterator, typename Container::iterator))
{
	for (unsigned int size = 20; size <= INT_MAX; size *= 2)
	{
		double	time = 0;
		std::cout << '\n' << "Size: " << size << std::endl;

		// Container				source = container_createAscend<Container>(size);
		Container				source = container_createAscend<Container>(size, -long(size / 2));
		std::random_shuffle(source.begin(), source.end());

		Container				container(source.begin(), source.end());
		{
			SimpleClock<MilliSeconds>	clock(clockName);

			ft_sort(container.begin(), container.end());
			time = clock.elapsed();
		}
		std::stringstream	message;

		if (!std::is_sorted(container.begin(), container.end()))
			message << "Not Sorted!: " << container;
		else if (time >= timeLimit)
			message << "[" << size << "] Timeout: " << time;
			// std::cout << "Timeout: " << time << "/" << timeLimit<< std::endl;
		else
			continue ;
		std::cout << "Result: {" << clockName << "}: " << message.str() << std::endl;
		break ;
	}
	// std::cerr << "Press enter to continue: ";
	// std::cin.get();
}

// template <typename Iterator>
// Iterator	partition(Iterator begin, Iterator end)
// {
// 	Iterator	pivot = end - 1;
// 	Iterator	i = begin - 1;

// 	for (Iterator j = begin; j != pivot; j++)
// 	{
// 		if (*j < *pivot)
// 		{
// 			i++;
// 			std::swap(*i, *j);
// 		}
// 	}
// 	std::swap(*(i + 1), *pivot);
// 	return (i + 1);
// }

// template <typename Iterator>
// Iterator	randomized_partition(Iterator begin, Iterator end)
// {
// 	std::random_shuffle(begin, end);
// 	return (partition(begin, end));
// }

// template <typename Iterator>
// void	quicksort(Iterator begin, Iterator end)
// {
// 	if (end - begin < 2)
// 		return ;
// 	Iterator	pivot = randomized_partition(begin, end);

// 	quicksort(begin, pivot);
// 	quicksort(pivot + 1, end);
// }

// template <typename Iterator>
// void	quicksort(Iterator begin, Iterator end)
// {
// 	if (end - begin < 2)
// 		return ;
// 	Iterator	pivot = partition(begin, end);

// 	quicksort(begin, pivot);
// 	quicksort(pivot + 1, end);
// }

bool	strmaxsize(const std::string &current, const std::string &element)
{
	return (current.size() < element.size());
}

template <typename Iterator>
void	radixstring(const Iterator begin, const Iterator end)
{
	typedef typename std::iterator_traits<Iterator>::value_type	String;
	typedef typename std::vector<String>						VectorString;
	typedef std::array<VectorString, 0x100>						BigBucket;

	BigBucket	bucket;
	// size_t		i = std::max_element(begin, end, strmaxsize)->size();
	size_t		i = std::max_element(begin, end, strmaxsize)->size();

	std::cout << "Max: " << i << std::endl;
	while (i--)
	{
		for (Iterator it = begin; it != end; it++)
		{
			const unsigned char	c = (i < it->size()) ? (*it)[i] : '\0';
			bucket[c].push_back(*it);
		}
		Iterator	arr = begin;
		for (typename BigBucket::iterator it = bucket.begin(); it != bucket.end(); it++)
		{
			std::copy(it->begin(), it->end(), arr);
			arr += it->size();
			it->clear();
		}
	}
}

int	main(int argc, char **argv)
{
	const unsigned int	timeLimit = 100;
	const std::string	strings[] = {
		"[Verse 1]",
		"Katachi no nai kimochi wasurenai you ni",
		"Kimari kitta reiauto wo keshita",
		"Futo kuchi zusanda fureezu wo tsukamaete",
		"Mune ni himeta kotoba nose sora ni toki hanatsu no",
		"",
		"[Chorus]",
		"Kimi ni tsutaetai koto ga",
		"Kimi ni todoketai koto ga",
		"Takusan no ten wa sen ni natte",
		"Tooku kanata e to hibiku",
		"Kimi ni tsutaetai kotoba",
		"Kimi ni todoketai oto ga",
		"Ikutsumo no sen wa en ni natte",
		"Subete tsunagete iku doko ni datte, ah-ah",
		"[Verse 2]",
		"Masshiro ni sunda hikari wa kimi no you",
		"Kazashita te no sukima wo tsutau koe ga",
		"Futo ugoita yubisaki kizamu rizumu ni",
		"Arittake no kotoba nose sora ni toki hanatsu no",
		"",
		"[Chorus]",
		"Kimi ni tsutaetai koto ga",
		"Kimi ni todoketai koto ga",
		"Takusan no ten wa sen ni natte",
		"Tooku kanata made ugatsu",
		"Kimi ni tsutaetai koto ga",
		"Kimi ni todoketai oto ga",
		"Ikutsumo no sen wa en ni natte",
		"Subete tsunagetе iku doko ni datte",
		"Ah-ah, ah-ah, ah-ah-ah-ah",
		"",
		"[Bridge]",
		"Kanadete ita kawaranai hibi wo utagawazu ni",
		"Asa wa darеka ga kureru mono da to omotte ita",
		"Isshun demo shinjita oto keshiki wo yurasu no",
		"Oshiete yo kimi dake no sekai",
		"",
		"[Chorus]",
		"Kimi ga tsutaetai koto wa",
		"Kimi ga todoketai koto wa",
		"Takusan no ten wa sen ni natte",
		"Tooku kanata e to hibiku",
		"Kimi ga tsutaetai kotoba",
		"Kimi ga todoketai oto wa",
		"Ikutsumono sen wa en ni natte",
		"Subete tsunageteku doko ni datte, ah-ah, ahhh",
	};
	const size_t	size = (sizeof(strings) / sizeof(strings[0]));

	
	// for (size_t i = 0; i < size; i++)
	// 	std::cout << strings[i] << std::endl;
	std::vector<std::string>	vstrings(strings, strings + size);
	radixstring(vstrings.begin(), vstrings.end());
	for (size_t i = 0; i < size; i++)
		std::cout << vstrings[i] << std::endl;
	std::cout << std::boolalpha << std::is_sorted(vstrings.begin(), vstrings.end()) << std::endl;
	// for (size_t i = 0; i < size; i++)
	// 	std::cout << strings[i] << std::endl;
	// test<Vector>(timeLimit, "BitRadix", bitwiseradixsort<Vector::iterator>);
	// test<Vector>(timeLimit, "Radix", MyRadix<Vector::iterator>);
#if 0
	// test<Vector>(timeLimit, "VectorMerge", MyMerge<Vector::iterator>);
	// test<Deque>(timeLimit, "DequeMerge", MyMerge<Deque::iterator>);
	// std::cerr << std::endl;

	test<Vector>(timeLimit, "BitRadix", BitRadix<Vector::iterator>);
	test<Vector>(timeLimit, "VectorRadix", MyRadix<Vector::iterator>);
	// test<Deque>(timeLimit, "DequeRadix", MyRadix<Deque::iterator>);
	// std::cerr << std::endl;
	// test<Vector>(timeLimit, "VectorInsertion", MyInsertion<Vector::iterator>);
	// test<Deque>(timeLimit, "DequeInsertion", MyInsertion<Deque::iterator>);
	// std::cerr << std::endl;
	// test<Vector>(timeLimit, "VectorQuick", MyQuick<Vector::iterator>);
	// test<Deque>(timeLimit, "DequeQuick", MyQuick<Deque::iterator>);
	test<Vector>(timeLimit, "VectorHybrid", TimSort<Vector::iterator>);
	std::cerr << std::endl;
	// std::cerr << std::endl;
	// test<Vector>(timeLimit, "VectorHeap", heapsort<Vector::iterator>);
	// test<Deque>(timeLimit, "DequeHeap", heapsort<Deque::iterator>);
	// std::cerr << std::endl;
	test<Vector>(timeLimit, "VectorSort", std::sort<Vector::iterator>);
	// test<Deque>(timeLimit, "DequeSort", std::sort<Deque::iterator>);
	std::cerr << std::endl;
	// test<Vector>(timeLimit, "VectorStable", std::stable_sort<Vector::iterator>);
	// test<Deque>(timeLimit, "DequeStable", std::stable_sort<Deque::iterator>);
	// std::cerr << std::endl;
#endif
}
