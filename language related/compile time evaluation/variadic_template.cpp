#include <iostream>

template<typename T>
void	print(T arg)
{
	std::cout << arg << std::endl;
}

template <typename T, typename... Args>
void	print(T arg, Args ...args)
{
	std::cout << arg << " ";
	print(args...);
}

/* Python print */
int main(void)
{
	print("adsda","asdsafa",12312323);
	print("line2","asulaafa",31323);
	print("Hatsune", "Miku", "love", "qixeo");
	print("qixeo", "love", "Hatsune", "Miku");
}
