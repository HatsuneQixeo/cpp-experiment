#include <algorithm>
#include <iostream>

/**
 * @brief Poggers, each type actually have their own static variable
 * 
 */

template <typename T>
T	increment(T data)
{
	static int call;

	std::cout << "call: " << ++call << std::endl;
	return (data + 1);
}

int	main(void)
{
	increment(1);
	increment(1.0f);
	increment(1.0);
	increment('a');
	increment(1);
	increment(1.0f);
	increment(1.0);
	increment('a');
}
