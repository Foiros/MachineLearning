//
// Created by arttu on 07/09/2021.
//

#ifndef MACHINELEARNING_DATAHANDLER_H
#define MACHINELEARNING_DATAHANDLER_H

#include <fstream>
#include "stdint.h"
#include "Data.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_set>


class DataHandler {

private:
    std::vector<Data*> *dataArray;
    std::vector<Data*> *trainingData;
    std::vector<Data*> *testData;
    std::vector<Data*> *validationData;

    int numClasses;
    int featureVectorSize;
    std::map<uint8_t, int> classMap;
    std::map<std::string, int> class_map;

    const double TRAIN_SET_PERCENT = 0.75;
    const double TEST_SET_PERCENT = 0.20;
    const double VALIDATION_PERCENT = 0.05;

public:
    DataHandler();
    ~DataHandler();

    void read_csv(std::string path, std::string delimiter);
    void ReadFeatureVector(std::string path);
    void ReadFeatureLabels(std::string path);
    void SplitData();
    void CountClasses();

    uint32_t ConvertToLittleEndian(const unsigned char* bytes);

    int Get_Class_Counts();
    std::vector<Data*> *GetTrainingData();
    std::vector<Data*> *GetTestData();
    std::vector<Data*> *GetValidationData();
};


#endif //MACHINELEARNING_DATAHANDLER_H
