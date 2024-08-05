#include <iostream>

class Log
{
	public:
		Log(void){std::cout << "Construct" << '\n';}
		~Log(void){std::cout << "Destruct" << '\n';}
};

/**
 * Temporary object lifetime last until the current line of expression ends (semicolon)
 * Make sense why const reference parameter works for temporary object now
 */
int	main(void)
{
	Log(), std::cout << "Log" << '\n';
}
