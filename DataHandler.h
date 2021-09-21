//
// Created by arttu on 07/09/2021.
//

#ifndef MACHINELEARNING_DATAHANDLER_H
#define MACHINELEARNING_DATAHANDLER_H

#include "fstream"
#include <cstdint>
#include "Data.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <cmath>


class DataHandler {

private:
    std::vector<Data*> *dataArray;
    std::vector<Data*> *trainingData;
    std::vector<Data*> *testData;
    std::vector<Data*> *validationData;

    int class_counts;
    int featureVectorSize;
    std::map<uint8_t, int> class_from_int;
    std::map<std::string, int> class_from_string;

    const double TRAIN_SET_PERCENT = 1;
    const double TEST_SET_PERCENT = 0.075;
    const double VALIDATION_PERCENT = 0.005;

public:
    DataHandler();
    ~DataHandler();

    void read_csv(std::string path, std::string delimiter);
    void Read_Input_Data(std::string path);
    void Read_Label_Data(std::string path);
    void SplitData();
    void CountClasses();
    void Normalize();
    void Print();

    int Get_Class_Counts();
    int Get_Data_Array_Size();
    int Get_Training_Data_Size();
    int Get_Test_Data_Size();
    int Get_Validation_Data_Size();

    uint32_t Format(const unsigned char* bytes);

    std::vector<Data*> *GetTrainingData();
    std::vector<Data*> *GetTestData();
    std::vector<Data*> *GetValidationData();
    std::map<uint8_t, int> Get_Class_Map();
};


#endif //MACHINELEARNING_DATAHANDLER_H
