#include <iostream>

/**
 * @brief Return value optimisation thing
 */
class RetStr
{
	private:
		std::string	str;

	public:
		RetStr(void){std::cout << "RetStr default construct" << '\n';}
		RetStr(const RetStr &){std::cout << "RetStr copy construct" << '\n';}
		RetStr	&operator=(const RetStr &){std::cout << "RetStr copy assignment" << '\n'; return (*this);}
};

RetStr	return_str(void)
{
	RetStr	ret;

	return (ret);
}

/* Heard this could disable return value optimisation, didn't occur in my experiments.
 * Don't think there's still any reason to justify this though.
 */
const RetStr	const_return_str(void)
{
	RetStr	ret;

	return (ret);
}

/* safe because const only apply in this function scope, I think */
RetStr	return_const_str(void)
{
	const RetStr	ret;

	return (ret);
}

int	main(void)
{
	{
		RetStr rs = return_str();
		(void)rs;
	}
	{
		RetStr crs = const_return_str();
		(void)crs;
	}
	{
		RetStr rcs = return_const_str();
		(void)rcs;
	}
	/*
		Return value optimisation can only occur during initialisation,
		since the variable hasn't has a definitive address just yet
	*/
	{
		RetStr rs;
		rs = return_str();
	}
}
