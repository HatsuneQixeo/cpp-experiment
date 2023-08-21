#include <iostream>

void	*retAddr(void *addr)
{
	return (addr);
}

int	main(void)
{
	std::cout << nullptr << std::endl;
	std::cout << (void *)0 << std::endl;
	std::cout << retAddr(nullptr) << std::endl;
}
