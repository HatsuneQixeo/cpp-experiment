#include <iostream>
#include <vector>

/**
 * @brief No idea what this is
 */

// template <void Call()>
// void	func(void)
// {
// 	Call();
// }

// void	printMiku(void)
// {
// 	std::cout << "Hatsune Miku" << std::endl;
// }

// template <typename Func>
// void	printIdk(Func func)
// {
// 	func();
// }

int	cmpI(const int &a, const int &b)
{
	return (1);
}

// template <typename T>
// int	cmp(const T a, const T b)
// {
// 	return (1);
// }

template <typename T, int Func(const T &, const T &)>
int	cmp(const T &a, const T &b)
{
	return (Func(a, b));
}

int	main(void)
{
	// const auto			ft = func<printMiku>;
	// printIdk(ft);
	std::vector<int>	vec;

	vec.push_back(39);
	vec.push_back(831);
	std::sort(vec.begin(), vec.end(), cmp<int, cmpI>);
}

class Miku
{};

template <class Miku>
void	miku(void)
{
	/* Calling the template */
	Miku();
	/* Calling the class because of global namespace */
	::Miku();
	/* Don't believe me? Try cmd/ctrl click on it */
}

void	name_collision(void)
{
	miku<Miku>();
	miku<int>();
}
