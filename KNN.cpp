//
// Created by arttu on 13/09/2021.
//

#include "KNN.h"
#include <cmath>
#include <limits>
#include <map>
#include "stdint.h"

KNN::KNN(int val) {

    k = val;
}

KNN::KNN() = default;

KNN::~KNN() = default;

// O(n^2) if K ~ N
// if K = 2 then O(~N)
// O(NLogN)
void KNN::Find_K_Nearest(Data *query_point) {

    neighbors = new std::vector<Data*>;
    double min = std::numeric_limits<double>::max();
    double previous_min = min;
    int index = 0;

    for (int i = 0; i < k; ++i) {
        
        if(i == 0){

            for (int j = 0; j < training_data->size(); ++j) {

                double distance = Calculate_Distance(query_point, training_data->at(j));
                training_data->at(j)->Set_Distance(distance);

                if(distance < min){

                    min = distance;
                    index = j;
                }
            }

            neighbors->push_back(training_data->at(index));
            previous_min = min;
            min = std::numeric_limits<double>::max();
        }
        else{

            for (int j = 0; j < training_data->size(); ++j) {

                double distance = training_data->at(j)->Get_Distance();

                if(distance > previous_min && distance < min){

                    min = distance;
                    index = j;
                }
            }

            neighbors->push_back(training_data->at(index));
            previous_min = min;
            min = std::numeric_limits<double>::max();
        }
    }
}

void KNN::Set_K(int val) {

    k = val;
}

int KNN::Predict() {

    std::map<uint8_t, int> class_freq;

    for (int i = 0; i < neighbors->size(); ++i) {

        if(class_freq.find(neighbors->at(i)->GetLabel()) == class_freq.end()){

            class_freq[neighbors->at(i)->GetLabel()] = 1;
        }
        else{

            class_freq[neighbors->at(i)->GetLabel()]++;
        }
    }

    int best = 0;
    int max = 0;

    for(auto kv : class_freq){

        if(kv.second > max){

            max = kv.second;
            best = kv.first;
        }
    }

    delete neighbors;
    return best;
}

double KNN::Calculate_Distance(Data *query_point, Data *input) {

    double distance = 0.0;
    if(query_point->GetFeatureVectorSize() != input->GetFeatureVectorSize()){

        printf("Error Vector Size Mismatch.\n");
        exit(1);
    }

#ifdef  EUCLID
    for(unsigned i = 0; i < query_point->GetFeatureVectorSize(); i++){

        distance += pow(query_point->GetFeatureVector()->at(i) - input->GetFeatureVector()->at(i), 2);
    }
    distance = sqrt(distance);
    return distance;

#elif defined MANHATTAN

#endif
}

double KNN::Validate_Performance() {

    double current_performance = 0;
    int count = 0;
    int data_index = 0;

    for(Data* query_point : *validation_data){

        Find_K_Nearest(query_point);
        int prediction = Predict();

        if(prediction == query_point->GetLabel())
            count++;


        data_index++;
        printf("Current Performance = %.3f %%\n", ((double) count * 100.0)/((double) data_index));
    }

    current_performance = ((double) count * 100.0)/((double) validation_data->size());
    printf("Validation Performance = %.3f %%\n", k, current_performance);
    return current_performance;
}

double KNN::Test_Performance() {

    double current_performance = 0;
    int count = 0;

    for(Data* query_point : *test_data){

        Find_K_Nearest(query_point);
        int prediction = Predict();

        if(prediction == query_point->GetLabel())
            count++;
    }

    current_performance = ((double ) count * 100.0/ ((double) test_data->size()));
    printf("Tested Performance = %.3f %%\n", current_performance);
    return current_performance;
}

double KNN::GetK() {
    return k;
}
