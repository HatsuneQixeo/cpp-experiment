#include <iostream>


/* throws std::out_of_range
	because -1 will be interpreted as SIZE_MAX by std::string::substr pos parameter size_t type,
	which is greater than the string size
	https://cplusplus.com/reference/string/string/substr/#:~:text=If%20this%20is%20greater%20than%20the%20string%20length%2C%20it%20throws%20out_of_range.
*/

int	main(void)
{
	std::string	str = "ha";

	size_t pos = str.find('b');
	std::cout << "str: " << str << '\n'; 
	std::cout << "pos: " << pos << '\n';
	try
	{
		const std::string	sub = str.substr(pos);
		std::cout << "sub: " << sub << '\n';
	}
	catch (const std::out_of_range &e)
	{
		std::cerr << "Out of range Exception: " << e.what() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}
