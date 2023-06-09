#include <iostream>

/*
	Did not ran into problem despite the warning in documentation.
	Can't say for sure this behaviour is consistent across every version tho.
	https://cplusplus.com/reference/string/string/front/
*/
int	main(int argc, char **argv)
{
	std::string	str;

	if (argc != 1)
		str = argv[1];
	try
	{
		std::cout << (int)str.front() << std::endl;
		str.clear();
		std::cout << (int)str.front() << std::endl;
		std::cout << "Good" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
