#include <iostream>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

template <typename Container>
int	trycallFront(const Container &container)
{
	typedef typename Container::value_type	T;

	const pid_t	pid = fork();
	int			status;

	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		const T	data = container.front();

		exit(0);
	}
	else if (waitpid(pid, &status, 0) == -1)
		return (-1);
	else if (WIFSIGNALED(status))
		throw (std::runtime_error(strsignal(WTERMSIG(status))));
	else
		return (status);
}

template <typename Container>
void	emptyFrontBackCall(Container container)
{
	try
	{
		std::cout << "size: " << container.size() << std::endl;
		{
			const auto	flags = std::cout.flags();

			std::cout << "data: 0x" << std::hex << reinterpret_cast<uintptr_t>(container.data()) << std::endl;
			std::cout.flags(flags);
		}
		const int	status = trycallFront(container);

		if (status == 0)
			std::cout << "Good" << std::endl;
		else
			std::cout << "Error code: " << status << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Program terminated: " << e.what() << std::endl;
	}
}

/*
	Did not crash std::string because string is always null terminated to support C function.
	This is not the case for container like std::vector that does not need a valid space yet.
*/
int	main(int argc, char **argv)
{
	std::cout << "str" << '\n';
	emptyFrontBackCall(std::string());
	std::cout << "vector" << '\n';
	emptyFrontBackCall(std::vector<int>());
	emptyFrontBackCall(std::vector<int>(0));
	emptyFrontBackCall(std::vector<int>(1));
	{
		std::vector<int>	vec;

		vec.push_back(1);
		vec.clear();
		emptyFrontBackCall(vec);
	}
}
