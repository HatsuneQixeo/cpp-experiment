#ifndef TEMPLATE_HPP
# define TEMPLATE_HPP

# include <iostream>

template <typename T>
void	log(const T &data)
{
	static unsigned int	called;

	std::cout << "Log(" << typeid(T).name() << ") call amount: " << ++called << std::endl;
	std::cout << data << std::endl;
}

#endif
