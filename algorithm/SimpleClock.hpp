#ifndef SIMPLECLOCK_HPP
# define SIMPLECLOCK_HPP

# include <iostream>

typedef std::chrono::microseconds	MilliSeconds;
typedef std::chrono::milliseconds	Seconds;

template <typename Unit>
class SimpleClock
{
	public:
		typedef std::chrono::steady_clock::time_point	Time;
		typedef Time	(*const GetTime)(void);

		static const GetTime	getCurrentTime;
	private:
		std::string	name;
		Time		start;

		/* Constructor && Destructor */
		SimpleClock(const SimpleClock &ref);

		/* OperatorOverload */
		SimpleClock	&operator=(const SimpleClock &ref);
	public:
		/* Constructor && Destructor */
		SimpleClock(const std::string &name);
		~SimpleClock(void);


		/* Getters */
		double	elapsed(void);
		void	rename(const std::string &newName);


		/* MemberFunctions */
};

template <typename Unit>
typename SimpleClock<Unit>::GetTime	SimpleClock<Unit>::getCurrentTime = std::chrono::high_resolution_clock::now;

/* Constructor && Destructor */
template <typename Unit>
SimpleClock<Unit>::SimpleClock(const std::string &name):
	name(name),
	start(getCurrentTime())
{}

template <typename Unit>
SimpleClock<Unit>::SimpleClock(const SimpleClock &ref)
{
	*this = ref;
}

template <typename Unit>
SimpleClock<Unit>::~SimpleClock(void)
{
	const double	duration = elapsed();

	std::cout << "[Clock]" << name << ": " << duration << std::endl;
	this->start = getCurrentTime();
}


/* Operator Overload */
template <typename Unit>
SimpleClock<Unit>	&SimpleClock<Unit>::operator=(const SimpleClock<Unit> &ref)
{
	/* Copy assignment */
	return (*this);
	(void)ref;
}


/* MemberFunctions */
template <typename Unit>
double	SimpleClock<Unit>::elapsed(void)
{
	const Time		now = getCurrentTime();
	const long long	duration = std::chrono::duration_cast<Unit>(now - this->start).count();

	return (duration * 0.001);
}

template <typename Unit>
void	SimpleClock<Unit>::rename(const std::string &newName)
{
	this->name = newName;
}

#endif
