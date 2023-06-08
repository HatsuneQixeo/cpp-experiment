#include <iostream>

int	main(void)
{
	std::string	str;

	try
	{
		std::cout << (int)str.front() << std::endl;
		std::cout << "Good" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
