#include <iostream>

/* c++ is not cursed at all :) */
int	main(void)
{
	int		i = 0;

	std::cout << (++(++(++(++i))))++ << std::endl;
	std::cout << (i += 2)++ << std::endl;
	std::cout << ++++++++++++++++++++++++++++i << std::endl;
}
