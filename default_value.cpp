#include <iostream>

template <typename T>
void	defaultValue(void)
{
	std::cout << T() << std::endl;
}

int	main(void)
{
	/* These are evaluated as function prototypes */
	unsigned int	n();
	std::string		s();
	/* Call to constructor */
	std::string		str = std::string();
	uint32_t		u = uint32_t();
	unsigned int	nbr = int();
	/* Casting */
	// unsigned int	nbr = (int)();
	/*
		By that logic, calling unsigned int constructor without typedef is pretty much impossible.
		Although it's possible with external function, not sure if it's even worth the overhead
	*/

	std::cout << int() << std::endl;
	// std::cout << (unsigned int)() << std::endl;
	defaultValue<int>();
	defaultValue<unsigned int>();
	defaultValue<long>();
	defaultValue<unsigned long>();
	defaultValue<unsigned char>();
	defaultValue<std::string>();
}
