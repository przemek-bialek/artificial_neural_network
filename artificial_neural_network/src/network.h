#pragma once
#include <fstream>
#include <vector>

class Neuron
{
	std::vector<double> m_weights;
	std::vector<double> m_inputs;
	double m_output;
public:
	void print_neuron();
	
	Neuron(const Neuron& other);
	Neuron(const int& amount, const bool& first_layer);

	void activation_function();

	double getOutput() const;

	void setInputs(const std::vector<double>& inputs);

	friend std::istream& operator >> (std::istream& in, Neuron& neuron);
	friend std::ostream& operator << (std::ostream& out, const Neuron& neuron);
};

class Layer
{
	std::vector<Neuron> m_neurons;
public:
	void print_layer();

	Layer(const Layer& other);
	Layer(const int& neurons_qtty, const int& inputs_qtty, const bool& first_layer);

	void feed_forward(Layer& next_layer);

	friend std::istream& operator >> (std::istream& in, Layer& layer);
	friend std::ostream& operator << (std::ostream& out, const Layer& layer);
};

class I_O
{
	std::ifstream m_in_file;

public:
	I_O(const std::string& in_filename);

	void get_data(Layer& input_layer);
	void print_data(const std::vector<Layer>& net, const std::string& out_filename);

	~I_O();
};