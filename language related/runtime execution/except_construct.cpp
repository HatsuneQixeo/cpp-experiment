#include <iostream>

/* A class that throws when constructed */
struct except_construct
{
	except_construct(void)
	{
		std::cerr << "except_construct constructor" << '\n';
		throw (std::exception());
	}

	~except_construct(void)
	{
		std::cerr << "except_construct destructor" << '\n';
	}
};

/* Overload new to show message during allocation */
void	*operator new(std::size_t size) throw(std::bad_alloc)
{
	void	*ptr = std::malloc(size);

	if (ptr == nullptr)
		throw (std::bad_alloc());
	std::cerr << "new: 0x" << ptr << std::endl;
	return (ptr);
}

/* Overload delete to show message during allocation */
void	operator delete(void *ptr) throw()
{
	std::free(ptr);
	std::cerr << "delete: 0x" << ptr << std::endl;
}

/* Program will call delete on new <constructor> throw directly
 * Destructor will not be invoked
*/
void	f()
{
	except_construct *ptr = new except_construct();

	std::cerr << "deleting after new statement" << '\n';
	delete ptr;
}

int	main(void)
{
	try
	{
		f();
	}
	catch (const std::exception &e)
	{
		std::cerr << "exception" << std::endl;
	}
}
