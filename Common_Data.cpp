//
// Created by arttu on 14/09/2021.
//

#include "Common_Data.h"

void Common_Data::Set_Training_Data(std::vector<Data *> *vector) {

    training_data = vector;
}

void Common_Data::Set_Test_Data(std::vector<Data *> *vector) {

    test_data = vector;
}

void Common_Data::Set_Validation_Data(std::vector<Data *> *vector) {

    validation_data = vector;
}
