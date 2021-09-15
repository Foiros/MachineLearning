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
    std::vector<double>* double_feature_Vector;
    std::vector<int>* class_vector;
    uint8_t label;
    int enumLabel; // A -> 1, B -> 2
    double distance;

public:
    Data();
    ~Data();

    void SetFeatureVector(std::vector<uint8_t>*);
    void AppendToFeatureVector(uint8_t);

    void Set_Double_Feature_Vector(std::vector<double>*);
    void Append_To_Double_Feature_Vector(double);

    void Set_Class_Vector(int count);


    void SetLabel(uint8_t);
    void SetEnumeratedLabel(int);
    void Set_Distance(double val);

    int GetFeatureVectorSize();
    uint8_t GetLabel();
    uint8_t GetEnumeratedLabel();

    std::vector<uint8_t>* GetFeatureVector();
    std::vector<double>* Get_Double_Feature_Vector();
    std::vector<int>* Get_Class_Vector();
    double Get_Distance();
};


#endif //MACHINELEARNING_DATA_H
