#include "networkPCH.h"
#include "network.h"

Layer::Layer(const Layer& other)
	:	neurons(other.neurons)
{
	std::cout << "Layer copied!\n";
}

Layer::Layer()
{
	std::cout << "Layer created!\n";
}

void Layer::init(const int& amount_of_neurons)
{
	neurons = new Neuron[amount_of_neurons];
	std::cout << "Layer initialized!\n";
}

Layer::~Layer()
{
	delete[] neurons;
}


Neuron::Neuron(const Neuron& other)
{
	std::cout << "Neuron copied!\n";
}

Neuron::Neuron()
{
	std::cout << "Neuron created!\n";
}

Neuron::~Neuron()
{

}