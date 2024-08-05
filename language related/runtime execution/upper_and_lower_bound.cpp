#include <algorithm>
#include <iostream>

void	showUpperLower(const int *const arr, const unsigned int length, const int value)
{
	const unsigned int	upper_index = std::upper_bound(arr, arr + length, value) - arr;
	const unsigned int	lower_index = std::lower_bound(arr, arr + length, value) - arr;

	std::cout << "upper_bound: " << upper_index << '\n';
	std::cout << "lower_bound: " << lower_index << '\n';
	std::cout << '\n';
}

/**
 * std::lower_bound returns the first element that is not less than the given value
 * std::upper_bound returns the first element that is greater than the given value
 */
int	main(void)
{
	const int			small = 39;
	const int			big = 831;
	const int 			arr[] = {small, small, small, big, big};
	const int			med = 831 - 39; // 792
	const unsigned int	length = (sizeof(arr) / sizeof(arr[0]));

	std::cout << "small" << '\n';
	showUpperLower(arr, length, small);
	std::cout << "big" << '\n';
	showUpperLower(arr, length, big);
	std::cout << "med" << '\n';
	showUpperLower(arr, length, med);
	std::cout << "small - 1" << '\n';
	showUpperLower(arr, length, small - 1);
	std::cout << "big + 1" << '\n';
	showUpperLower(arr, length, big + 1);
	std::cout << "1" << '\n';
	showUpperLower(arr, length, 1);
	std::cout << "1000" << '\n';
	showUpperLower(arr, length, 1000);
}
