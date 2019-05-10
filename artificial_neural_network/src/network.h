#pragma once

class Neuron
{
public:
	Neuron(const Neuron& other);
	Neuron();

	~Neuron();
};

class Layer
{
	Neuron* neurons;
public:
	Layer(const Layer& other);
	Layer();

	void init(const int& amount_of_neurons);

	~Layer();
};