#include <iostream>

template <typename T>
void	defaultValue(void)
{
	std::cout << T() << std::endl;
}

class Show
{
	public:
		Show(void)
		{
			std::cout << "Show default constructor" << std::endl;
		}
		~Show(void)
		{
			std::cout << "Show destructor" << std::endl;
		}
		Show(const std::string &str)
		{
			std::cout << "Show constructor with string: " << str << std::endl;
		}
		Show(const Show &other)
		{
			std::cout << "Show copy constructor" << std::endl;
			*this = other;
		}
		Show	&operator=(const Show &other)
		{
			std::cout << "Show copy assignment operator" << std::endl;
			return (*this);
		}
};

int	main(void)
{
	/*
		These are evaluated as function prototypes.
		Kinda makes sense, this is not you'd typically invoke default constructor anyway.
		Imagine actually prototyping like this tho.
	*/
	unsigned int	n();
	Show			ft1();
	Show			ft2(std::string str);
	/* Call to constructor */
	Show			s("Hatsune Miku is cute");
	Show			str = Show();
	uint32_t		u = uint32_t();
	unsigned int	nbr = int();
	/* Casting */
	// unsigned int	nbr = (int)(); /* does not compile */
	/*
		By that logic, invoking unsigned int constructor without typedef is pretty much impossible.
		Although it's possible with external function,
		it's far from practical for reasons not worth mentioning under this experiment.

		But to be honest, nothing in here has any practical value.
		= 0/{} already does it during initialisation,
		and static_cast<unsigned int>(0) for non initialisation context.
		Not to mention the intention is much clearer.
	*/

	std::cout << int() << std::endl;
	// std::cout << (unsigned int)() << std::endl; /* does not compile */
	defaultValue<int>();
	defaultValue<unsigned int>();
	defaultValue<long>();
	defaultValue<void *>();
	defaultValue<unsigned long>();
	defaultValue<unsigned char>();
	defaultValue<std::string>();
}
