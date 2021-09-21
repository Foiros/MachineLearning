//
// Created by arttu on 20/09/2021.
//

#include "Network.h"
#include "DataHandler.h"
#include <numeric>

Network::Network(std::vector<int> hidden_layer_spec, int input_size, int num_classes, double learning_rate) {

    for (int i = 0; i < hidden_layer_spec.size(); ++i) {

        if(i == 0)
            layers.push_back(new Layer(input_size, hidden_layer_spec.at(i)));
        else
            layers.push_back(new Layer(layers.at(i-1)->neurons.size(), hidden_layer_spec.at(i)));
    }

    layers.push_back(new Layer(layers.at(layers.size()-1)->neurons.size(), num_classes));
    this->learning_rate = learning_rate;
}

Network::~Network() = default;

double Network::Activate(std::vector<double> weigths, std::vector<double> inputs) {

    double activation = weigths.back(); // Last element, bias term

    for (int i = 0; i < weigths.size() - 1; ++i) {

        activation += weigths[i] * inputs[i];
    }

    return activation;
}

double Network::Transfer(double activation) {

    return 1.0 / (1.0 + exp(-activation));
}

double Network::Transfer_Derivative(double output) {

    return output * (1 - output);
}

std::vector<double> Network::F_Prop(Data *data) {

    std::vector<double> inputs = *data->Get_Normalized_Feature_Vector();

    for (int i = 0; i < layers.size(); ++i) {

        Layer* layer = layers.at(i);
        std::vector<double> new_inputs;

        for (Neuron *neuron : layer->neurons) {

            double activation = this->Activate(neuron->Get_Weights(), inputs);
            neuron->output = this->Transfer(activation);
            new_inputs.push_back(neuron->output);
        }

        inputs = new_inputs;
    }

    return inputs; // Output layer outputs aka predictions
}

void Network::B_Prop(Data *data) {

    for (int i = layers.size() - 1; i >= 0; --i) {

        Layer* layer = layers.at(i);
        std::vector<double> errors;

        if(i != layers.size() -1){

            for (int j = 0; j < layer->neurons.size(); ++j) {

                double error = 0.0;

                for (Neuron* neuron : layers.at(i + 1)->neurons) {

                    error += (neuron->Get_Weights().at(j) * neuron->delta);
                }

                errors.push_back(error);
            }
        }
        else{

            for (int j = 0; j < layer->neurons.size(); ++j) {

                Neuron* neuron = layer->neurons.at(j);
                errors.push_back((double) data->Get_Class_Vector()->at(j) - neuron->output); // Expected - actual
            }
        }

        for (int j = 0; j < layer->neurons.size(); ++j) {

            Neuron* neuron = layer->neurons.at(j);
            neuron->delta = errors.at(j) * this->Transfer_Derivative(neuron->output); // Gradient / derivative part of back prop.
        }
    }
}

void Network::Update_Weights(Data *data) {

    std::vector<double> inputs = *data->Get_Normalized_Feature_Vector();

    for (int i = 0; i < layers.size(); ++i) {

        if(i != 0){

            for(Neuron *neuron : layers.at(i -1)->neurons){

                inputs.push_back(neuron->output);
            }
        }

        for(Neuron* neuron : layers.at(i)->neurons){

            for(int j = 0; j < inputs.size(); j++){

                neuron->Get_Weights().at(j) += this->learning_rate * neuron->delta * inputs.at(j);
            }

            neuron->Get_Weights().back() += this->learning_rate * neuron->delta;
        }

        inputs.clear();
    }
}

int Network::Predict(Data *data) {

    std::vector<double> outputs = F_Prop(data);

    return std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end()));
}

void Network::Train(int num_epochs) {

    for (int i = 0; i < num_epochs; ++i) {

        double sum_error = 0.0;

        for (Data* data : *this->training_data) {

            std::vector<double> outputs = F_Prop(data);
            std::vector<int> expected = data->Get_Class_Vector();
            double temp_error_sum = 0.0;

            for (int j = 0; j < outputs.size(); ++j) {

                temp_error_sum += pow((double) expected.at(j) - outputs.at(j), 2);
            }

            sum_error += temp_error_sum;
            B_Prop(data);
            Update_Weights(data);
        }

        printf("Iteration: %d \t Error=%.4f\n", i, sum_error);
    }
}

double Network::Test() {

    double num_correct = 0.0;
    double count = 0.0;

    for (Data* data : *this->test_data) {

        count++;
        int index = Predict(data);
        if(data->Get_Class_Vector()->at(index) == 1) num_correct++;
    }

    test_performance = (num_correct / count);
    return test_performance;
}

void Network::Validate() {

    double num_correct = 0.0;
    double count = 0.0;

    for (Data* data : *this->validation_data) {

        count++;
        int index = Predict(data);
        if(data->Get_Class_Vector()->at(index) == 1) num_correct++;
    }

    printf("Validation Performance: %.4f \n", num_correct / count);
}
