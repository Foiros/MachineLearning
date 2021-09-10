//
// Created by arttu on 07/09/2021.
//

#include "DataHandler.h"

DataHandler::DataHandler() {

    dataArray = new std::vector<Data*>;
    testData = new std::vector<Data*>;
    trainingData = new std::vector<Data*>;
    validationData = new std::vector<Data*>;
}

DataHandler::~DataHandler() {

}

void DataHandler::ReadFeatureVector(std::string path) {

    uint32_t  header[4]; // |Magic|Num Images|RowSize|ColSize
    unsigned char bytes[4];
    FILE* file = fopen(path.c_str(), "rb");

    if(file){

        for (int i = 0; i < 4; i++) {

            if(fread(bytes, sizeof(bytes), 1, file)){
                i = ConvertToLittleEndian(bytes);
            }
        }

        printf("Done Getting Input File Header.\n");

        int imageSize = header[2]*header[3];
        for (int i = 0; i < header[1]; ++i) {

            Data* data = new Data();
            uint8_t  element[1];

            for (int j = 0; j < imageSize; ++j) {

                if(fread(element, sizeof(element), 1, file)){

                    data->AppendToFeatureVector(element[0]);
                }
                else{
                    printf("Error Reading from File.\n");
                    exit(1);
                }
            }

            dataArray->push_back(data);
        }

        printf("Successfully read and stored %u feature vectors.\n", dataArray->size());
    }
    else{
        printf("Couldn't find file.\n");
        exit(1);
    }
}

void DataHandler::ReadFeatureLabels(std::string path) {

    uint32_t  header[2]; // |Magic|Num Images
    unsigned char bytes[4];
    FILE* file = fopen(path.c_str(), "rb");

    if(file){

        for (unsigned int & i : header) {

            if(fread(bytes, sizeof(bytes), 1, file)){
                i = ConvertToLittleEndian(bytes);
            }
        }

        printf("Done Getting Label File Header.\n");

        for (int i = 0; i < header[1]; ++i) {

            uint8_t  element[1];

            if(fread(element, sizeof(element), 1, file)){

                dataArray->at(i)->SetLabel(element[0]);
            }
            else{
                printf("Error Reading from File.\n");
                exit(1);
            }
        }

        printf("Successfully read and stored %u labels.\n", dataArray->size());
    }
    else{
        printf("Couldn't find file.\n");
        exit(1);
    }
}

void DataHandler::SplitData() {

    std::unordered_set<int> usedIndexes;
    int trainSize = dataArray->size() * TRAIN_SET_PERCENT;
    int testSize = dataArray->size() * TEST_SET_PERCENT;
    int validSize = dataArray->size() * VALIDATION_PERCENT;

    // Training Data
    int count = 0;
    while(count < trainSize){

        int randomIndex = rand() % dataArray->size();
        if(usedIndexes.find(randomIndex) == usedIndexes.end()){

            trainingData->push_back(dataArray->at(randomIndex));
            usedIndexes.insert(randomIndex);
            count++;
        }
    }

    // Test Data
    count = 0;
    while(count < testSize){

        int randomIndex = (rand() + rand()) % dataArray->size();
        if(usedIndexes.find(randomIndex) == usedIndexes.end()){

            testData->push_back(dataArray->at(randomIndex));
            usedIndexes.insert(randomIndex);
            count++;
        }
    }

    // Validation Data
    count = 0;
    while(count < validSize){

        int randomIndex = rand() % dataArray->size();
        if(usedIndexes.find(randomIndex) == usedIndexes.end()){

            validationData->push_back(dataArray->at(randomIndex));
            usedIndexes.insert(randomIndex);
            count++;
        }
    }

    printf("Training Data Size: %u.\n", trainingData->size());
    printf("Test Data Size: %u.\n", testData->size());
    printf("Validation Data Size: %u.\n", validationData->size());
}

void DataHandler::CountClasses() {

    int count = 0;
    for(unsigned i = 0; i < dataArray->size(); i++){

        if(classMap.find(dataArray->at(i)->GetLabel()) == classMap.end()){

            classMap[dataArray->at(i)->GetLabel()] = count;
            dataArray->at(i)->SetEnumeratedLabel(count);
            count++;
        }
    }
    numClasses = count;
    printf("Successfully Extracted %d Unique Classes.\n", numClasses);
}

uint32_t DataHandler::ConvertToLittleEndian(const unsigned char *bytes) {

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
