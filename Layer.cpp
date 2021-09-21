//
// Created by arttu on 20/09/2021.
//

#include "Layer.h"

Layer::Layer(int previous_layer_size, int current_layer_size) {

    for (int i = 0; i < current_layer_size; ++i) {

        neurons.push_back(new Neuron(previous_layer_size, current_layer_size));
    }

    this->current_layer_size = current_layer_size;
}

Layer::~Layer() = default;
