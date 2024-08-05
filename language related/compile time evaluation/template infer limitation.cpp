#include <iostream>

template <typename T, class Callable>
void	printF(const T &ref, const Callable &f)
{
	std::cout << "CONCRETE" << '\n';
}

/*
	This only applies to object, not type.
	Meaning Class<T> would prefer this overload instead of concrete type overload.

	Nothing could infer and take in template with incomplete type.

	printF(1, res) is not possible.
	printF(1, res<int>) is possible as concrete type.

	printF(1, Res) is not possible.
	printF(1, Res<int>) is not possible.
	printF(1, Res<int>()) is possible as template class type.

	Comment this function out,
	and the template class will still compile with concrete type overload.
*/
template <typename T, template <typename> class Callable>
void	printF(const T &ref, const Callable<T> &f)
{
	std::cout << "INFERRED" << '\n';
}

template <typename T>
struct Res
{
	const T	&operator()(const T &ref) const
	{
		return (ref);
	}
};

template <typename T>
const T	&res(const T &ref)
{
	return (ref);
}

int	main(void)
{
	printF(1, res<int>); // concrete
	printF(1, Res<int>()); // inferred
}
