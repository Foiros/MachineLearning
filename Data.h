//
// Created by arttu on 07/09/2021.
//

#ifndef MACHINELEARNING_DATA_H
#define MACHINELEARNING_DATA_H

#include <vector>
#include <cstdint>
#include <cstdio>


class Data {

private:
    std::vector<uint8_t>* featureVector; // No class at end.
    uint8_t label;
    int enumLabel; // A -> 1, B -> 2

public:
    Data();
    ~Data();

    void SetFeatureVector(std::vector<uint8_t>*);
    void AppendToFeatureVector(uint8_t);
    void SetLabel(uint8_t);
    void SetEnumeratedLabel(int);

    int GetFeatureVectorSize();
    uint8_t GetLabel();
    uint8_t GetEnumeratedLabel();

    std::vector<uint8_t>* GetFeatureVector();
};


#endif //MACHINELEARNING_DATA_H
