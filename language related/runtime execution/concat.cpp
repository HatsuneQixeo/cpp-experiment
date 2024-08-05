#include <iostream>
#include "SimpleClock.hpp"

/**
 * Is concatinating string and then write to std::cout faster?
 * 
 * Yes, and things get's even worse my multiple magnitude if it's std::endl instead of '\n'
 * 
 * That said, writing directly is still more preferable if the timing is sensitive
 * And the performance impact shouldn't be too noticeable if there's not like ten thousand iteration at once
 * 
 * And no, this test did not include memory usage, it's surely ugly to see.
 * It should be relatively *easy to optimise by just clearing the buffer once in a while though.
 * 
 * *: I don't mean easy by easy across every devices and situation of course,
 * not that I've ever ran out of memory myself just yet.
 * 
 * What about number? Would it be still faster to convert it into string and concatenate them?
 * There's your answer, not surprised somehow.
 * Writing integer is even slower for some reason
 */

const std::string	Miku = "Hatsune Miku";
const unsigned int	MikuBirthday = 83139831;
const size_t		iterations = 10000000;

void	concat(void)
{
	std::string	str;

	for (unsigned int i = 0; i < iterations; i++)
		str += Miku;
	std::cout << str;
}

void	directStr(void)
{
	for (unsigned int i = 0; i < iterations; i++)
		std::cout << Miku;
}

void	toString(void)
{
	std::string	str;

	for (unsigned int i = 0; i < iterations; i++)
		str += std::to_string(MikuBirthday);
	std::cout << str;
}

void	directInt(void)
{
	for (unsigned int i = 0; i < iterations; i++)
		std::cout << MikuBirthday;
}

/* This is even faster than directInt SOMEHOW, like HOW???????????????? */
void	directToString(void)
{
	for (unsigned int i = 0; i < iterations; i++)
		std::cout << std::to_string(MikuBirthday);
}

#define MEASURE(func)	{ \
	SimpleClock<MilliSeconds>	clock(#func); \
	func;\
}

int	main(void)
{
	MEASURE(concat())
	MEASURE(directStr())
	MEASURE(toString())
	MEASURE(directInt())
	MEASURE(directToString())
}
