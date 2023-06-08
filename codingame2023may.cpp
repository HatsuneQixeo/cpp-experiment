#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
T	read(void)
{
	T	data;

	std::cin >> data;
	return (data);
}

template <class Container>
void	show_container(const Container &container)
{
	std::for_each(container.begin(), container.end(), [](const typename Container::value_type &ele)
	{
		std::cerr << ele << std::endl;
	});
}

typedef std::array<int, 6>	Neighbours;

class Cell
{
	private:
	public:
		int			type;
		int			initial_resources;
		Neighbours	neighbours;
		void	read(void)
		{
			std::cin >> this->type >> this->initial_resources;
			for (int &ele : this->neighbours)
				std::cin >> ele;  
			std::cin.ignore();
		}
		friend std::ostream	&operator<<(std::ostream &output, const Cell &cell)
		{
			output
				<< "type: " << cell.type << '\n'
				<< "initial_resources: " << cell.initial_resources << '\n';
			show_container(cell.neighbours);
		}
};

int main(void)
{
	const int			number_of_cells = read<int>(); std::cin.ignore();
	std::vector<Cell>	arr_cells(number_of_cells);

	for (Cell &ele : arr_cells)
		ele.read();
	const int			number_of_bases = read<int>(); std::cin.ignore();
	std::vector<int>	my_base(number_of_bases);
	std::vector<int>	oppo_base(number_of_bases);


	std::for_each(my_base.begin(), my_base.end(), [](int &ele)
	{
		ele = read<int>();
	});
	std::for_each(oppo_base.begin(), oppo_base.end(), [](int &ele)
	{
		ele = read<int>();
	});

	// game loop
	while (1)
	{
		for (int i = 0; i < number_of_cells; i++)
		{
			int resources; // the current amount of eggs/crystals on this cell
			int my_ants; // the amount of your ants on this cell
			int opp_ants; // the amount of opponent ants on this cell
			std::cin >> resources >> my_ants >> opp_ants; std::cin.ignore();
		}

		// WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
		std::cout << "WAIT" << std::endl;
	}
}
