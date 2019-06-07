#include "networkPCH.h"
#include "network.h"

static const double e = std::exp(1);

I_O::I_O(const std::string& in_filename)
{
	m_in_file.open(in_filename);
	if (m_in_file.is_open())
		std::cout << "\"" << in_filename << "\" opened successfully as input\n";
	else
		throw("Could not open \"" + in_filename + "\"");
}

void I_O::get_data(Layer& input_layer)
{
	if (m_in_file.is_open())
	{
		m_in_file >> input_layer;
	}
	else
		throw("Training file is not open");
}

void I_O::print_data(const std::vector<Layer>& net, const std::string& out_filename)
{
	std::ofstream file;
	file.open(out_filename);
	if (file.is_open())
	{
		for (unsigned i = 0; i < net.size(); i++)
			file << net[i];
		file.close();
	}
	else
		throw "Could not open \"" + out_filename + "\"";
}

I_O::~I_O()
{
	m_in_file.close();
}


Neuron::Neuron(const Neuron& other)
	: m_output(other.m_output), m_weights(other.m_weights), m_inputs(other.m_inputs)
{
	std::cout << "Neuron copied!\n";
}

Neuron::Neuron(const int& amount, const bool& first_layer)
{	
	m_weights.reserve(amount);
	m_inputs.reserve(amount);
	if (!first_layer)
	{
		for (int i = 0; i < amount; i++)
			m_weights.emplace_back(2.0 * ((double)rand() / (double)RAND_MAX) - 1.0);
	}
	else
		for (int i = 0; i < amount; i++)
			m_weights.emplace_back(1.0);
	m_inputs.emplace_back(1);
	m_output = 1;
	std::cout << "Neuron created!\n";
}

void Neuron::activation_function()
{
	double sum = 0.0;

	for (unsigned i = 0; i < m_inputs.size(); i++)
		sum += m_inputs[i] * m_weights[i];

	m_output = sum / (1 + pow(e, -sum));
}

double Neuron::getOutput() const
{
	return m_output;
}

void Neuron::setInputs(const std::vector<double>& inputs)
{
	m_inputs = inputs;
}

std::istream& operator >> (std::istream& in, Neuron& neuron)
{
	in >> neuron.m_inputs[0];
	neuron.m_output = neuron.m_inputs[0];
	return in;
}

std::ostream& operator << (std::ostream& out, const Neuron& neuron)
{
	for (unsigned i = 0; i < neuron.m_weights.size(); i++)
		out << neuron.m_weights[i] << " ";
	return out;
}


Layer::Layer(const Layer& other)
	: m_neurons(other.m_neurons)
{
	std::cout << "Layer copied!\n";
}

Layer::Layer(const int& neurons_qtty, const int& inputs_qtty, const bool& first_layer)
{
	m_neurons.reserve(neurons_qtty);
	for (int i = 0; i < neurons_qtty; i++)
		m_neurons.emplace_back(inputs_qtty, first_layer);

	std::cout << "Layer created!\n";
}

void Layer::feed_forward(Layer& next_layer)
{
	std::vector<double> tmp;
	tmp.reserve(m_neurons.size());
	for (unsigned i = 0; i < tmp.capacity(); i++)
		tmp.emplace_back(m_neurons[i].getOutput());
	for (unsigned i = 1; i < next_layer.m_neurons.size(); i++)
	{
		next_layer.m_neurons[i].setInputs(tmp);
		next_layer.m_neurons[i].activation_function();
	}
}

std::istream& operator >> (std::istream& in, Layer& layer)
{
	for (int i = 1; i < layer.m_neurons.size(); i++)
		in >> layer.m_neurons[i];
	return in;
}

std::ostream& operator << (std::ostream& out, const Layer& layer)
{
	for (unsigned i = 0; i < layer.m_neurons.size(); i++)
		out << layer.m_neurons[i] << "\n";
	return out;
}




void Neuron::print_neuron()
{
	std::cout << "inputs\tweights\n";
	for (unsigned i = 0; i < m_inputs.size(); i++)
		std::cout << m_inputs[i] << "\t" << m_weights[i] << "\n";
	std::cout << "output " << m_output << "\n";
	std::cout << "capacity " << m_inputs.capacity() << "\n";
}
void Layer::print_layer()
{
	
	for (unsigned i = 0; i < m_neurons.size(); i++)
	{
		std::cout << "neuron " << i << "\n";
		m_neurons[i].print_neuron();
		std::cout << "\n";
	}
	std::cout << "end of layer\n\n";
}