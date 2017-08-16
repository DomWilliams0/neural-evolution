#include <random>
#include "neural.h"
#include "config.h"

NeuralNetwork::NeuralNetwork(std::initializer_list<unsigned int> layers) {
    OpenNN::Vector<size_t> architecture(layers.begin(), layers.end());
    net.set(architecture);

    // outputs 0-1
    net.construct_probabilistic_layer();

    // random parameters/weights/biases
    net.randomize_parameters_normal();
}

void NeuralNetwork::copyAndMutate(NeuralNetwork *out) const {

    // random generator
    static std::random_device rd;
    static std::mt19937 gen_uniform(rd());
    static std::mt19937 gen_normal(rd());

    static std::uniform_real_distribution<> dis_uniform(0, 1);
    static std::normal_distribution<> dis_normal(Config::MUTATE_NORMAL_MEAN, Config::MUTATE_NORMAL_SD);

    OpenNN::Vector<double> params = net.arrange_parameters();

    // mutate randomly
    for (auto it = params.begin(); it != params.end(); ++it) {
        double chance = dis_uniform(gen_uniform);
        if (chance > Config::MUTATE_WEIGHT_CHANCE)
            continue;

        double variation = dis_normal(gen_normal);
        *it += variation;
    }

    out->net.set(net.arrange_architecture());
    out->net.set_parameters(params);
}

void NeuralNetwork::tick(const std::vector<double> &inputs, std::vector<double> &outputs) {
    OpenNN::Vector<double> converted(inputs.cbegin(), inputs.cend());
    outputs = net.calculate_outputs(converted);
}

