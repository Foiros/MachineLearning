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
