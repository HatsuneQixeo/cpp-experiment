#include <iostream>
#include <vector>
#include <stack>
#include <array>

/**
 * @brief Trying to make sure that classes are nested and printed out properly.
 */

struct Child
{
	typedef std::vector<Child>	Children;
	const std::string	name;
	Children			children;

	Child(const std::string &name, const Children &children = Children()):
		name(name),
		children(children)
	{}
};

std::string	operator*(const std::string &src, const unsigned int count)
{
	std::string	str;

	str.reserve(src.size() * count);
	for (unsigned int i = 0; i < count; ++i)
		str += src;
	return (str);
}

std::ostream	&operator<<(std::ostream &os, const Child &child)
{
	std::stack<std::pair<const Child *, unsigned int> >	stack;

	stack.push(std::make_pair(&child, 0));
	while (!stack.empty())
	{
		const Child		*current = stack.top().first;
		unsigned int	&index = stack.top().second;
		const std::string	pad = std::string("  ") * (stack.size() - 1);

		if (current->children.size() == 0)
		{
			os << pad << current->name;
			stack.pop();
		}
		else if (index < current->children.size())
		{
			if (index == 0)
				os << pad << current->name << ":\n" << pad << "[";
			else
				os << ",";
			os << '\n';
			stack.push(std::make_pair(&current->children[index], 0));
			++index;
		}
		else if (index == current->children.size())
		{
			stack.pop();
			os << '\n' << pad << "]";
		}
		else
		{
			std::cerr << "undefined" << '\n';
		}
	}
	return (os);
}

int	main(void)
{
	Child::Children	children1;
	Child::Children	children2;
	Child::Children	children;

	children1.push_back(Child("child1_1"));
	children1.push_back(Child("child1_2"));
	children2.push_back(Child("child2_1"));
	children2.push_back(Child("child2_2"));
	children.push_back(Child("child1", children1));
	children.push_back(Child("child2", children2));

	std::cout << Child("root", children) << std::endl;
	return (0);
}
