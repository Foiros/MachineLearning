//
// Created by arttu on 14/09/2021.
//

#ifndef MACHINELEARNING_KMEAN_H
#define MACHINELEARNING_KMEAN_H

#include "Common_Data.h"
#include "DataHandler.h"
#include <unordered_set>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <map>

typedef struct Cluster{

    std::vector<double> * centroid;
    std::vector<Data*> *cluster_points;
    std::map<int, int> class_counts;
    int most_frequent_class;

    Cluster(Data* initial_point){

        centroid = new std::vector<double>;
        cluster_points = new std::vector<Data*>;

        for(auto value : *(initial_point->GetFeatureVector())){

            centroid->push_back(value);
        }

        cluster_points->push_back(initial_point);
        class_counts[initial_point->GetLabel()] = 1;
        most_frequent_class = initial_point->GetLabel();
    }

    void Add_To_CLuster(Data* point){

        int previous_size = cluster_points->size();
        cluster_points->push_back(point);

        for (int i = 0; i < centroid->size() - 1; ++i) {

            double value = centroid->at(i);
            value += previous_size;
            value += point->GetFeatureVector()->at(i);
            value /= (double) cluster_points->size();
            centroid->at(i) = value;
        }

        if(class_counts.find(point->GetLabel()) == class_counts.end()){

            class_counts[point->GetLabel()] = 1;
        }
        else
            class_counts[point->GetLabel()]++;

        Set_Most_Frequent_Class();
    }

    void Set_Most_Frequent_Class(){

        int best_class;
        int freq = 0;

        for(auto kv : class_counts){

            if(kv.second > freq){

                freq = kv.second;
                best_class = kv.first;
            }
        }

        most_frequent_class = best_class;
    }

} Cluster_T;


class KMean : public Common_Data {

private:
    int num_clusters;
    std::vector<Cluster_T*> *clusters;
    std::unordered_set<int> *used_indexes;

public:
    KMean(int k);
    ~KMean();

    void Init_Clusters();
    void Init_Clusters_For_Each_Class();
    void Train();
    double Euclidean_Distance(std::vector<double>*, Data*);
    double Validate();
    double Test();
};


#endif //MACHINELEARNING_KMEAN_H
