//
// Created by arttu on 07/09/2021.
//

#include "DataHandler.h"
#include <algorithm>
#include <random>

DataHandler::DataHandler() {

    dataArray = new std::vector<Data*>;
    testData = new std::vector<Data*>;
    trainingData = new std::vector<Data*>;
    validationData = new std::vector<Data*>;
}

DataHandler::~DataHandler() = default;

void DataHandler::read_csv(std::string path, std::string delimiter) {

    class_counts = 0;
    std::ifstream  data_file;
    data_file.open(path.c_str());
    std::string line; // Holds each line

    while(std::getline(data_file, line)){

        if(line.length() == 0) continue;
        Data *d = new Data();
        d->Set_Normalized_Feature_Vector(new std::vector<double>());
        size_t position = 0;
        std::string token; // Value in between delimiter

        while((position = line.find(delimiter)) != std::string::npos){

            token = line.substr(0, position);
            d->Append_To_Feature_Vector(std::stod(token));
            line.erase(0, position + delimiter.length());
        }

        if(class_from_string.find(line) != class_from_string.end()){

            d->SetLabel(class_from_string[line]);
        }
        else{

            class_from_string[line] = class_counts;
            d->SetLabel(class_from_string[line]);
            class_counts++;
        }

        dataArray->push_back(d);
    }

    for(Data* data: *dataArray)
        data->Set_Class_Vector(class_counts);

    featureVectorSize = dataArray->at(0)->Get_Normalized_Feature_Vector()->size();
}


void DataHandler::Read_Input_Data(std::string path) {

    uint32_t  magic = 0;
    uint32_t  num_images = 0;
    uint32_t  num_rows = 0;
    uint32_t num_cols = 0;

    unsigned char bytes[4];
    FILE* file = fopen(path.c_str(), "r");

    if(file){

        int i = 0;

        while (i < 4){

            if(fread(bytes, sizeof(bytes), 1, file))
            {
                switch(i)
                {
                    case 0:
                        magic = Format(bytes);
                        i++;
                        break;
                    case 1:
                        num_images = Format(bytes);
                        i++;
                        break;
                    case 2:
                        num_rows = Format(bytes);
                        i++;
                        break;
                    case 3:
                        num_cols = Format(bytes);
                        i++;
                        break;
                }
            }
        }

        printf("Done Getting File Header.\n");
        
        uint32_t image_size = num_rows * num_cols;

        for (int j = 0; j < num_images; ++j) {
            
            Data* data = new Data();
            data->SetFeatureVector(new std::vector<uint8_t>());
            uint8_t  element[1];

            for (int k = 0; k < image_size; ++k) {

                if(fread(element, sizeof(element), 1, file)){

                    data->AppendToFeatureVector(element[0]);
                }
            }

            dataArray->push_back(data);
            dataArray->back()->Set_Class_Vector(class_counts);
        }

        Normalize();
        featureVectorSize = dataArray->at(0)->GetFeatureVector()->size();
        printf("Successfully Read %lu Data Entries.\n", dataArray->size());
        printf("The Feature Vector Size is: %d\n", featureVectorSize);
    }
    else{

        printf("Invalid Input File Path\n");
        exit(1);
    }
}

void DataHandler::Read_Label_Data(std::string path) {

    uint32_t magic = 0;
    uint32_t num_images = 0;
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "r");

    if(f)
    {
        int i = 0;
        while(i < 2)
        {
            if(fread(bytes, sizeof(bytes), 1, f))
            {
                switch(i)
                {
                    case 0:
                        magic = Format(bytes);
                        i++;
                        break;
                    case 1:
                        num_images = Format(bytes);
                        i++;
                        break;
                }
            }
        }

        for(unsigned j = 0; j < num_images; j++)
        {
            uint8_t element[1];
            if(fread(element, sizeof(element), 1, f))
            {
                dataArray->at(j)->SetLabel(element[0]);
            }
        }

        printf("Done getting Label header.\n");
    }
    else
    {
        printf("Invalid Label File Path\n");
        exit(1);
    }
}

void DataHandler::SplitData() {

    std::unordered_set<int> usedIndexes;
    int train_size = dataArray->size() * TRAIN_SET_PERCENT;
    int test_size = dataArray->size() * TEST_SET_PERCENT;
    int valid_size = dataArray->size() * VALIDATION_PERCENT;

    std::random_shuffle(dataArray->begin(), dataArray->end());

    // Training Data
    int count = 0;
    int index = 0;

    while(count < train_size)
    {
        trainingData->push_back(dataArray->at(index++));
        count++;
    }

    // Test Data
    count = 0;

    while(count < test_size)
    {
        testData->push_back(dataArray->at(index++));
        count++;
    }

    // Test Data

    count = 0;
    while(count < valid_size)
    {
        validationData->push_back(dataArray->at(index++));
        count++;
    }

    printf("Training Data Size: %lu.\n", trainingData->size());
    printf("Test Data Size: %lu.\n", testData->size());
    printf("Validation Data Size: %lu.\n", validationData->size());
}



void DataHandler::CountClasses() {

    int count = 0;

    for(unsigned i = 0; i < dataArray->size(); i++)
    {
        if(class_from_int.find(dataArray->at(i)->GetLabel()) == class_from_int.end())
        {
            class_from_int[dataArray->at(i)->GetLabel()] = count;
            dataArray->at(i)->SetEnumeratedLabel(count);
            count++;
        }
        else
        {
            dataArray->at(i)->SetEnumeratedLabel(class_from_int[dataArray->at(i)->GetLabel()]);
        }
    }

    class_counts = count;
    for(Data *data : *dataArray)
        data->Set_Class_Vector(class_counts);
    printf("Successfully Extraced %d Unique Classes.\n", class_counts);
}

void DataHandler::Normalize() {

    std::vector<double> mins, maxs;

    Data* data = dataArray->at(0);

    for (auto val : *data->GetFeatureVector()) {

        mins.push_back(val);
        maxs.push_back(val);
    }

    for (int i = 0; i < dataArray->size(); ++i) {

        data = dataArray->at(i);

        for (int j = 0; j < data->GetFeatureVectorSize(); ++j) {

            double value = (double) data->GetFeatureVector()->at(j);

            if(value < mins.at(j)) mins[j] = value;
            if(value > maxs.at(j)) maxs[j] = value;
        }
    }

    for (int i = 0; i < dataArray->size(); ++i) {

        dataArray->at(i)->SetNormalizedFeatureVector(new std::vector<double>());
        dataArray->at(i)->Set_Class_Vector(class_counts);

        for (int j = 0; j < dataArray->at(i)->GetFeatureVectorSize(); ++j) {

            if(maxs[j] - mins[j] == 0) dataArray->at(i)->AppendToFeatureVector(0.0);
            else
                dataArray->at(i)->AppendToFeatureVector((double) (dataArray->at(i)->GetFeatureVector()->at(j) - mins[j]) / (maxs[j] - mins[j]));
        }
    }
}

int DataHandler::Get_Class_Counts() {

    return class_counts;
}

int DataHandler::Get_Data_Array_Size(){

    return dataArray->size();
}

int DataHandler::Get_Training_Data_Size(){

    return trainingData->size();
}

int DataHandler::Get_Test_Data_Size(){

    return testData->size();
}

int DataHandler::Get_Validation_Data_Size(){

    return validationData->size();
}

uint32_t DataHandler::Format(const unsigned char *bytes) {

    return (uint32_t) ((bytes[0] << 24) | (bytes[1] << 16 | (bytes[2] << 8) | (bytes[3])));
}


std::vector<Data *> * DataHandler::GetTrainingData() {

    return trainingData;
}

std::vector<Data *> * DataHandler::GetTestData() {

    return testData;
}

std::vector<Data *> * DataHandler::GetValidationData() {

    return validationData;
}

std::map<uint8_t, int> DataHandler::Get_Class_Map() {

    return class_from_int;
}


void DataHandler::Print() {

    printf("Training Data:\n");
    for(auto data : *trainingData)
    {
        for(auto value : *data->Get_Normalized_Feature_Vector())
        {
            printf("%.3f,", value);
        }
        printf(" ->   %d\n", data->GetLabel());
    }
    return;

    printf("Test Data:\n");
    for(auto data : *testData)
    {
        for(auto value : *data->Get_Normalized_Feature_Vector())
        {
            printf("%.3f,", value);
        }
        printf(" ->   %d\n", data->GetLabel());
    }

    printf("Validation Data:\n");
    for(auto data : *validationData)
    {
        for(auto value : *data->Get_Normalized_Feature_Vector())
        {
            printf("%.3f,", value);
        }
        printf(" ->   %d\n", data->GetLabel());
    }
}




