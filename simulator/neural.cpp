#include <random>
#include "neural.h"
#include "config.h"

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> &layers) {
    OpenNN::Vector<size_t> architecture(layers.begin(), layers.end());
    net.set(architecture);

    // random parameters/weights/biases
    net.randomize_parameters_normal();
}

NeuralNetwork::NeuralNetwork() : NeuralNetwork(Config::NET_LAYERS) {
}

void NeuralNetwork::copyAndMutate(NeuralNetwork *out) const {

    // random generator
    static std::random_device rd;
    static std::mt19937 gen_uniform(rd());
    static std::mt19937 gen_normal(rd());

    static std::uniform_real_distribution<> dis_uniform(0, 1);
    static std::normal_distribution<> dis_normal(Config::MUTATE_NORMAL_MEAN, Config::MUTATE_NORMAL_SD);

    out->net.set(net);
    OpenNN::Vector<double> params = out->net.arrange_parameters();

    // mutate randomly
    for (auto it = params.begin(); it != params.end(); ++it) {
        double chance = dis_uniform(gen_uniform);
        if (chance > Config::MUTATE_WEIGHT_CHANCE)
            continue;

        double variation = dis_normal(gen_normal);
        *it += variation;
    }
    out->net.set_parameters(params);
}

void NeuralNetwork::tick(const std::vector<double> &inputs, std::vector<double> &outputs) {
    OpenNN::Vector<double> converted(inputs.cbegin(), inputs.cend());
    outputs = net.calculate_outputs(converted);
}

unsigned int NeuralNetwork::getInputCount() const {
    return net.get_inputs_number();
}

