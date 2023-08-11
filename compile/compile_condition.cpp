#include <iostream>
#include <vector>
#include <list>

/**
 * @brief Not compatible with school's compiler
 * 
 * It does not support constexpr, <aa<bb>>, etc..
 * 
 */

void	basic(void)
{
	if constexpr (1)
		std::cout << "Hatsune Miku" << std::endl;
	else if constexpr (2)
		std::cout << "is cute" << std::endl;
	else
		std::cout << "Hatsune Miku is cute" << std::endl;
}

template <class Container>
void	templateType(void)
{
	typedef typename Container::value_type	T;
	typedef typename Container::allocator_type	Alloc;

	if constexpr (std::is_same<std::vector<T, Alloc>, Container>::value)
		std::cout << "Is vector" << std::endl;
	else if constexpr (std::is_same<std::list<T, Alloc>, Container>::value)
		std::cout << "Is list" << std::endl;
	else
		std::cout << "Is Unknown" << std::endl;
}

int	main(void)
{
	templateType<std::vector<int>>();
	templateType<std::list<int>>();
}
