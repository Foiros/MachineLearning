#include <iostream>
#include "DataHandler.h"
#include "KNN.h"
#include "KMean.h"
#include "Network.h"

int main() {

    auto* data_handler = new DataHandler();

#ifdef MNIST
    data_handler->Read_Input_Data("../train-images-idx3-ubyte");
    data_handler->Read_Label_Data("../trains-labels-idx1-ubyte");
    data_handler->Count_Classes();

#else
    data_handler->read_csv("..iris.data", ",");

#endif
    data_handler->SplitData();
    std::vector<int> hidden_layers = {10};

    auto lambda = [&](){

        Network* network = new Network(hidden_layers, data_handler->GetTrainingData()->at(0)->Get_Normalized_Feature_Vector()->size(),
                                       data_handler->Get_Class_Counts(), 0.25);

        network->Set_Training_Data(data_handler->GetTrainingData());
        network->Set_Test_Data(data_handler->GetTestData());
        network->Set_Validation_Data(data_handler->GetValidationData());
        network->Train(15);
        network->Validate();
        printf("Test Performance: %.3f\n", network->Test());
    };

    lambda();

    return 0;
}