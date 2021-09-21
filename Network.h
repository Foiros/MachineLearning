//
// Created by arttu on 20/09/2021.
//

#ifndef MACHINELEARNING_NETWORK_H
#define MACHINELEARNING_NETWORK_H

#include "Data.h"
#include "Neuron.h"
#include "Layer.h"
#include "Common_Data.h"

class Network : public Common_Data{

private:
//    InputLayer* input_layer;
//    OutputLayer* output_layer;
//    std::vector<HiddenLayer*> hidden_layers;
//    double eta; // Learning rate

    std::vector<Layer*> layers;
    double learning_rate;
    double test_performance;

public:
    Network(std::vector<int>  hidden_layer_spec, int, int, double);
    ~Network();

    std::vector<double> F_Prop(Data* data);
    double Activate(std::vector<double>, std::vector<double>); // Dot product
    double Transfer(double);
    double Transfer_Derivative(double); // Used for backprop
    void B_Prop(Data* data);
    void Update_Weights(Data* data);
    int Predict(Data* data);
    void Train(int); // Number of iterations
    double Test();
    void Validate();
};


#endif //MACHINELEARNING_NETWORK_H
