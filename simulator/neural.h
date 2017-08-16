#ifndef NEURAL_EVOLUTION_NEURAL_H
#define NEURAL_EVOLUTION_NEURAL_H

#include <neural_network.h>

class NeuralNetwork {

protected:
    OpenNN::NeuralNetwork net;

public:
    NeuralNetwork(std::initializer_list<unsigned int> layers);

    void copyAndMutate(NeuralNetwork *out) const;

    void tick(const std::vector<double> &inputs, std::vector<double> &outputs);
};


#endif
