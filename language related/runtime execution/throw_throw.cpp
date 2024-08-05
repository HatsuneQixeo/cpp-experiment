#include <iostream>

/* Caught the way it is interpreted as during throw */
int	main(void)
{
	try
	{
		try
		{
			throw (std::runtime_error("error"));
		}
		catch (const std::exception &e)
		{
			throw (e); /* std::exception */
			// throw (dynamic_cast<const std::runtime_error &>(e)); /* runtime_error */
		}
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << "runtime_error" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "exception" << std::endl;
	}
}
