#include <cstdio>

/**
 * @brief Default argument + virtual is the root of all evil
 * https://stackoverflow.com/a/12140116
 */
class Base
{
	public:
		virtual void f(int a = 1)
		{
			printf("Base::f(%d)\n", a);
		}
};

class Deriv : public Base
{
	public:
		void f(int a = 2)
		{
			printf("Deriv::f(%d)\n", a);
		}
};

int main()
{
	Base* a = new Deriv();
	a->f();
	delete a;
	return 0;
}
