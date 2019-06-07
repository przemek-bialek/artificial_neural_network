#include <iostream>
#include <string>
#include "network.h"

template <typename T>
void insert_value(T& var)
{
	std::cin >> var;
	while (!std::cin)
	{
		std::cout << "Input correct number\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> var;
	}
}

void insert_filename(std::string& name)
{
	std::cin >> name;
	int size = name.size();
	if (size < 4)
	{
		name += ".txt";
		return;
	}
	std::string tmp;
	for (int i = size - 4; i < size; i++)
		tmp += name[i];
	if (tmp != ".txt" && tmp != ".TXT")
		name += ".txt";
}

void init_net(std::vector<Layer>& layers)
{
	int amount;
	int neurons_amount;
	int tmp = 1;

	std::cout << "How many layers do you want to create?\n";
	insert_value(amount);
	if (amount <= 0)
		throw("yeeaaaaaa very funny");
	layers.reserve(amount);
	std::cout << "Bias neurons will be added by application itself\n";
	for (int i = 0; i < amount; i++)
	{
		if (i == amount - 1)
			std::cout << "Insert amount of neurons in the output layer\n";
		else
			if (i == 0)
				std::cout << "Insert amount of neurons in the input layer\n";
			else
			std::cout << "Insert amount of neurons in the next layer\n";
		insert_value(neurons_amount);
		neurons_amount += 1;
		if (neurons_amount <= 0)
			throw("yeeaaaaaa very funny");
		if (i == 0)
			layers.emplace_back(neurons_amount, tmp, true);
		else
			layers.emplace_back(neurons_amount, tmp, false);
		tmp = neurons_amount;
	}
}

void print_net(std::vector<Layer>& net)
{
	for (unsigned i = 0; i < net.size(); i++)
		net[i].print_layer();
}

int main()
{
	try
	{
		std::cout << "Atificial Neural Network\n\n";
		
		I_O files("training_data.txt");
		std::vector<Layer> net;
		init_net(net);
		std::cout << "\nafter init\n";
		print_net(net);
		files.get_data(net[0]);
		std::cout << "\nafter get\n";
		print_net(net);
		for (unsigned i = 0; i < net.size() - 1; i++)
		{
			net[i].feed_forward(net[i + 1]);
			std::cout << "\nafter first feed\n";
			print_net(net);
		}
		std::cout << "\n\n\nfinal results\n";
		print_net(net);
	}
	catch (const std::string& exception)
	{
		std::cout << exception << "\n";
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}