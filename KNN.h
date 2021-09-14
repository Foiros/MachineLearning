//
// Created by arttu on 13/09/2021.
//

#ifndef MACHINELEARNING_KNN_H
#define MACHINELEARNING_KNN_H

#include <vector>
#include "Common_Data.h"


class KNN : public Common_Data {

private:
    double k;
    std::vector<Data*> *neighbors;
    std::vector<Data*> *training_data;
    std::vector<Data*> *test_data;
    std::vector<Data*> *validation_data;

public:
    KNN(int val);
    KNN();
    ~KNN();

    void Find_K_Nearest(Data* query_point);
    void Set_K(int val);

    int Predict();
    double Calculate_Distance(Data* query_point, Data* input);
    double Validate_Performance();
    double Test_Performance();

    double GetK();
};


#endif //MACHINELEARNING_KNN_H
