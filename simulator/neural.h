#ifndef NEURAL_EVOLUTION_NEURAL_H
#define NEURAL_EVOLUTION_NEURAL_H

#include <neural_network.h>

class NeuralNetwork {

protected:
    OpenNN::NeuralNetwork net;

    void setArchitecture(const OpenNN::Vector<size_t> &layers);

public:
    NeuralNetwork(const std::vector<unsigned int> &layers);

    NeuralNetwork();

    void copyAndMutate(NeuralNetwork *out) const;

    void tick(const std::vector<double> &inputs, std::vector<double> &outputs);

    unsigned int getInputCount() const;
};


#endif
