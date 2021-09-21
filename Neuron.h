//
// Created by arttu on 20/09/2021.
//

#ifndef MACHINELEARNING_NEURON_H
#define MACHINELEARNING_NEURON_H

#include <cstdio>
#include <cmath>
#include <vector>


class Neuron {

private:
    std::vector<double> weights;
    double pre_activation;
    double activated_output;
    double output_derivative;
    double error;
    double alpha; // used in activation functions

public:
    double output;
    double delta;

public:
    Neuron(int, int);
    ~Neuron();

    void Initialize_Weights(int previous_layer_size);
    void Set_Error(double);
    void Set_Weight(double, int);
    double Calculate_Pre_Activation(std::vector<double>);
    double Activate();
    double Calculate_Output_Derivate();
    double Sigmoid();
    double Relu();
    double Leaky_Relu();
    double Inverse_Sqrt_Relu();
    double Get_Output();
    double Get_Output_Derivative();
    double Get_Error();
    std::vector<double> Get_Weights();
};


#endif //MACHINELEARNING_NEURON_H
