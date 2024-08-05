#include <iostream>

/**
 * @brief Kind of an anti-pattern?
 */

struct TypeErasure
{
	private:
		struct inner_base
		{
			virtual ~inner_base(void) {}

			virtual std::ostream			&print(std::ostream &os) const = 0;
			virtual const std::type_info	&type(void) const = 0;
		};

		template <typename T>
		struct inner_t: inner_base
		{
			const T	&data;

			inner_t(const T &data): data(data) {}

			std::ostream	&print(std::ostream &os) const
			{
				return (os << data);
			}

			const std::type_info	&type(void) const
			{
				return (typeid(T));
			}
		};

	private:
		inner_base	*inner;

	public:
		template <typename T>
		static TypeErasure	make(T &data)
		{
			// static_assert)
			return (TypeErasure(new inner_t<T>(data)));
		}

		inner_base	*operator->(void) const { return inner; }

		~TypeErasure(void) { delete inner; }
	private:
		TypeErasure(inner_base *inner): inner(inner) {}
		TypeErasure(void) {}
};

std::ostream	&operator<<(std::ostream &os, const TypeErasure &ref)
{
	return (ref->print(os));
}

struct TestClass
{
	TestClass(void)
	{
		std::cout << "TestClass::TestClass(void)" << std::endl;
	}
	~TestClass(void)
	{
		std::cout << "TestClass::~TestClass" << std::endl;
	}
};

std::ostream	&operator<<(std::ostream &os, const TestClass &ref)
{
	return (os << "TestClass");
}

int	main(void)
{
	/* Following three examples are undefined behavior (Not holding object lifetime) */
	{
		// TypeErasure	test1 = TypeErasure::make(std::string("Hatsune Miku is cute a a a  a a a a "));
		// TypeErasure	test2 = TypeErasure::make(TestClass());
		// TypeErasure	test3 = TypeErasure::make(39);

		// std::cout << test1 << '\n';
		// std::cout << test2 << '\n';
		// std::cout << test3 << '\n';
	}

	int	data = 42;
	std::cout << TypeErasure::make(data) << '\n';
	/* Should be fine as string literal share the same lifetime as program */
	std::cout << TypeErasure::make("Hatsune Miku is cute") << '\n';
	const char	c = 'c';
	std::cout << TypeErasure::make(c) << '\n';
	const int	n = 39;
	std::cout << TypeErasure::make(n) << '\n';
}
