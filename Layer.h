//
// Created by arttu on 20/09/2021.
//

#ifndef MACHINELEARNING_LAYER_H
#define MACHINELEARNING_LAYER_H

#include "Neuron.h"
#include <stdint.h>
#include <vector>

static int layerID = 0;

class Layer {

public:
    int current_layer_size;
    std::vector<Neuron*> neurons;
    std::vector<double> layer_outputs;

    Layer(int, int);
    ~Layer();
};


#endif //MACHINELEARNING_LAYER_H
