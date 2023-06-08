#include <iostream>

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (0);
	std::string	str = argv[1];

	std::cout << static_cast<const void *>(str.data()) << std::endl;
	std::cout << str.data() << std::endl;
	str.~basic_string();
	std::cout << static_cast<const void *>(str.data()) << std::endl;
	std::cout << str.data() << std::endl;
}
