#include <numeric>
#include <vector>
#include "algorithm/SimpleClock.hpp"

#ifndef MAX
# define MAX	100
#endif

/**
 * @brief Generally, there not much of a runtime difference to a point of worry.
 * 
 */

typedef std::vector<int>	C;

C	getC(void)
{
	C	c(100000);
	const size_t	size = c.size();

	std::iota(c.begin(), c.end(), 0);
	for (unsigned int i = 0; i < size; i++)
		std::swap(c[i], c[rand() % size]);
	return (c);
}

void	local(int a,int b, C &c)
{
	if (c.begin() == c.end())
		return ;
	for (C::iterator it = c.begin(); it !=  c.end() - 1; ++it)
		std::swap(it[0], it[1]);
}

void	pointer(int a, int b, C *const c)
{
	if (c->begin() == c->end())
		return ;
	for (C::iterator it = c->begin(); it != c->end() - 1; ++it)
		std::swap(it[0], it[1]);
}

void	direct(int a, int b, C c)
{
	if (c.begin() == c.end())
		return ;
	for (C::iterator it = c.begin(); it !=  c.end() - 1; ++it)
		std::swap(it[0], it[1]);
}

void	literallyInside(int a, int b)
{
	C	c = getC();

	if (c.begin() == c.end())
		return ;
	for (C::iterator it = c.begin(); it !=  c.end() - 1; ++it)
		std::swap(it[0], it[1]);
}

int	main(void)
{
	unsigned int	n = 39;

	{
		SimpleClock<MilliSeconds>	clock("local");
		for (unsigned int i = 0; i < MAX; i++)
		{
			C	c = getC();
			local(n, n, c);
		}
	}
	{
		SimpleClock<MilliSeconds>	clock("pointer");
		for (unsigned int i = 0; i < MAX; i++)
		{
			C	c = getC();
			pointer(n, n, &c);
		}
	}
	{
		SimpleClock<MilliSeconds>	clock("direct");
		for (unsigned int i = 0; i < MAX; i++)
			direct(n, n, getC());
	}
	{
		SimpleClock<MilliSeconds>	clock("literallyInside");
		for (unsigned int i = 0; i < MAX; i++)
			literallyInside(n, n);
	}
}
