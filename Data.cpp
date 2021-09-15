//
// Created by arttu on 07/09/2021.
//

#include "Data.h"

Data::Data() {

    featureVector = new std::vector<uint8_t>;
}

Data::~Data() {

}

void Data::SetFeatureVector(std::vector<uint8_t> * vector) {

    featureVector = vector;
}

void Data::AppendToFeatureVector(uint8_t val) {

    featureVector->push_back(val);
}

void Data::SetLabel(uint8_t val) {

    label = val;
}

void Data::SetEnumeratedLabel(int val) {

    enumLabel = val;
}

int Data::GetFeatureVectorSize() {

    return featureVector->size();
}

uint8_t Data::GetLabel() {

    return label;
}

uint8_t Data::GetEnumeratedLabel() {

    return enumLabel;
}

std::vector<uint8_t> *Data::GetFeatureVector() {

    return featureVector;
}

void Data::Set_Distance(double val) {

    distance = val;
}

double Data::Get_Distance() {

    return distance;
}

void Data::Set_Double_Feature_Vector(std::vector<double> *vector) {

    double_feature_Vector = vector;
}

void Data::Append_To_Double_Feature_Vector(double val) {

    double_feature_Vector->push_back(val);
}

void Data::Set_Class_Vector(int count) {

    class_vector = new std::vector<int>;

    for (int i = 0; i < count; ++i) {

        if(i == label)
            class_vector->push_back(1);
        else
            class_vector->push_back(0);
    }
}

std::vector<double> *Data::Get_Double_Feature_Vector() {
    return nullptr;
}

std::vector<int> *Data::Get_Class_Vector() {
    return nullptr;
}
