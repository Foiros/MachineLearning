//
// Created by arttu on 20/09/2021.
//

#ifndef MACHINELEARNING_HIDDENLAYER_H
#define MACHINELEARNING_HIDDENLAYER_H

#include "Layer.h"

class HiddenLayer : public Layer{

public:
    HiddenLayer(int prev, int current) : Layer(prev, current){}
    void Feed_Forward(Layer prev);
    void Back_Prop(Layer next);
    void Update_Weights(double, Layer*);
};


#endif //MACHINELEARNING_HIDDENLAYER_H
