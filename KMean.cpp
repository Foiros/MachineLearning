//
// Created by arttu on 14/09/2021.
//

#include "KMean.h"

KMean::KMean(int k) {

    num_clusters = k;
    clusters = new std::vector<Cluster_T*>;
    used_indexes = new std::unordered_set<int>;
}

KMean::~KMean() = default;

void KMean::Init_Clusters() {

    for (int i = 0; i < num_clusters; ++i) {

        int index = (rand() % training_data->size());

        while(used_indexes->find(index) != used_indexes->end()){

            index = (rand() % training_data->size());
        }

        clusters->push_back(new Cluster(training_data->at(index)));
        used_indexes->insert(index);
    }
}

void KMean::Init_Clusters_For_Each_Class() {

    std::unordered_set<int> classes_used;

    for (int i = 0; i < training_data->size(); ++i) {

        if(classes_used.find(training_data->at(i)->GetLabel()) == classes_used.end()){

            clusters->push_back(new Cluster_T(training_data->at(i)));
            classes_used.insert(training_data->at(i)->GetLabel());
            used_indexes->insert(i);
        }
    }
}

void KMean::Train() {

    int index = 0;

    while(used_indexes->size() < training_data->size()){

        while (used_indexes->find(index) != used_indexes->end()){

            index++;
        }

        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = 0;

        for (int i = 0; i < clusters->size(); ++i) {

            double current_dist = Euclidean_Distance(clusters->at(i)->centroid, training_data->at(index));

            if(current_dist < min_dist){

                min_dist = current_dist;
                best_cluster = i;
            }
        }

        clusters->at(best_cluster)->Add_To_CLuster(training_data->at(index));
        used_indexes->insert(index);
    }

}

double KMean::Euclidean_Distance(std::vector<double> *_centroid, Data *point) {

    double dist = 0.0;

    for (int i = 0; i < _centroid->size(); ++i) {

        dist += pow(_centroid->at(i) - point->GetFeatureVector()->at(i), 2);
    }

    return sqrt(dist);
}

double KMean::Validate() {

    double num_correct = 0.0;

    for(auto query_point : *validation_data){

        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = 0;

        for (int i = 0; i < clusters->size(); ++i) {

            double current_dist = Euclidean_Distance(clusters->at(i)->centroid, query_point);

            if(current_dist < min_dist){

                min_dist = current_dist;
                best_cluster = i;
            }
        }

        if(clusters->at(best_cluster)->most_frequent_class == query_point->GetLabel())
            num_correct++;
    }

    return 100.0 * (num_correct / (double) validation_data->size());
}

double KMean::Test() {

    double num_correct = 0.0;

    for(auto query_point : *test_data){

        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = 0;

        for (int i = 0; i < clusters->size(); ++i) {

            double current_dist = Euclidean_Distance(clusters->at(i)->centroid, query_point);

            if(current_dist < min_dist){

                min_dist = current_dist;
                best_cluster = i;
            }
        }

        if(clusters->at(best_cluster)->most_frequent_class == query_point->GetLabel())
            num_correct++;
    }

    return 100.0 * (num_correct / (double) test_data->size());
}
