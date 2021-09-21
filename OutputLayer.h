//
// Created by arttu on 20/09/2021.
//

#ifndef MACHINELEARNING_OUTPUTLAYER_H
#define MACHINELEARNING_OUTPUTLAYER_H

#include "Layer.h"
#include "Data.h"


class OutputLayer : public Layer {

public:
    OutputLayer(int prev, int current) : Layer(prev, current){}

    void Feed_Forward(Layer);
    void Back_Prop(Data* data);
    void Update_Weights(double, Layer*);
};


#endif //MACHINELEARNING_OUTPUTLAYER_H
