#include <iostream>

/*
	Actually crashes if the string is large enough.
	Might have to do with some optimisation done in std::string for small size string

	Explicitly calling the destructor just leads to a lot of problems in general,
	since the object will be in put into invalid state (whatever that means),
	double free,
	forfeiting virtual properties,
	crashes,
	undefined behaviour,
	just to name a few.
*/
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
