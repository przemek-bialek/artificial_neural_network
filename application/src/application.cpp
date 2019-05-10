#include <iostream>
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

Layer* init()
{
	int amount;
	int neurons_amount;

	std::cout << "How many layers do you want to create?\n";
	insert_value(amount);
	if (amount <= 0)
		throw("yeeaaaaaa very funny");
	Layer* layers = new Layer[amount];
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
		if (neurons_amount <= 0)
			throw("yeeaaaaaa very funny");
		layers[i].init(neurons_amount);
	}
	return layers;
}

int main()
{
	try
	{
		std::cout << "Atificial Neural Network\n\n";
		
		Layer* layers = init();
	}
	catch (const char* exception)
	{
		std::cout << exception << "\n";
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}