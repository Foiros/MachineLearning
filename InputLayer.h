//
// Created by arttu on 20/09/2021.
//

#ifndef MACHINELEARNING_INPUTLAYER_H
#define MACHINELEARNING_INPUTLAYER_H

#include "Layer.h"
#include "Data.h"

class InputLayer : public Layer {

public:
    InputLayer(int prev, int current) : Layer(prev, current){};

    void Set_LayerOutputs(Data* data);
};


#endif //MACHINELEARNING_INPUTLAYER_H
