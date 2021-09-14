//
// Created by arttu on 14/09/2021.
//

#ifndef MACHINELEARNING_COMMON_DATA_H
#define MACHINELEARNING_COMMON_DATA_H

#include "Data.h"
#include <vector>


class Common_Data {

protected:
    std::vector<Data*> *training_data;
    std::vector<Data*> *test_data;
    std::vector<Data*> *validation_data;

public:
    void Set_Training_Data(std::vector<Data*> *vector);
    void Set_Test_Data(std::vector<Data*> *vector);
    void Set_Validation_Data(std::vector<Data*> *vector);
};


#endif //MACHINELEARNING_COMMON_DATA_H
