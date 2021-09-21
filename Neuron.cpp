//
// Created by arttu on 20/09/2021.
//

#include "Neuron.h"
#include <random>

double Generate_Random_Number(double min, double max){

    double random = (double) rand() / RAND_MAX;
    return min + random * (max - min);
}

Neuron::Neuron(int previous_layer_size, int current_layer_size) {

    Initialize_Weights(previous_layer_size);
}

Neuron::~Neuron() = default;

void Neuron::Initialize_Weights(int previous_layer_size) {

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < previous_layer_size + 1; ++i) {

        weights.push_back(Generate_Random_Number(-1.0, 1.0));
    }
}

void Neuron::Set_Error(double) {

}

void Neuron::Set_Weight(double, int) {

}

double Neuron::Calculate_Pre_Activation(std::vector<double>) {
    return 0;
}

double Neuron::Activate() {
    return 0;
}

double Neuron::Calculate_Output_Derivate() {
    return 0;
}

double Neuron::Sigmoid() {
    return 0;
}

double Neuron::Relu() {
    return 0;
}

double Neuron::Leaky_Relu() {
    return 0;
}

double Neuron::Inverse_Sqrt_Relu() {
    return 0;
}

double Neuron::Get_Output() {
    return 0;
}

double Neuron::Get_Output_Derivative() {
    return 0;
}

double Neuron::Get_Error() {
    return 0;
}

std::vector<double> Neuron::Get_Weights() {

    return weights;
}
