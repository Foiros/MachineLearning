#include <iostream>
#include "DataHandler.h"
#include "KNN.h"
#include "KMean.h"

int main() {

    auto* dh = new DataHandler();
    dh->ReadFeatureVector("../train-images-idx3-ubyte");
    dh->ReadFeatureLabels("../train-labels-idx1-ubyte");
    dh->SplitData();
    dh->CountClasses();

    KNN* k_nearest = new KNN();
    k_nearest->Set_Training_Data(dh->GetTrainingData());
    k_nearest->Set_Test_Data(dh->GetTestData());
    k_nearest->Set_Validation_Data(dh->GetValidationData());

    double performance = 0;
    double best_performance = 0;
    int best_k = 1;

    for (int k = dh->Get_Class_Counts(); k < dh->GetTrainingData()->size() * 0.1; ++k) {

        KMean *km = new KMean(k);
        km->Set_Training_Data(dh->GetTrainingData());
        km->Set_Test_Data(dh->GetTestData());
        km->Set_Validation_Data(dh->GetValidationData());
        km->Init_Clusters();
        km->Train();

        performance = km->Validate();
        printf("Current Performance @ K = %d: %.2f\n", k, performance);

        if(performance > best_performance){

            best_performance = performance;
            best_k = k;
        }
    }

    KMean *km = new KMean(best_k);
    km->Set_Training_Data(dh->GetTrainingData());
    km->Set_Test_Data(dh->GetTestData());
    km->Set_Validation_Data(dh->GetValidationData());
    km->Init_Clusters();

    performance = km->Test();
    printf("Tested Performance @ K = %d: %.2f\n", best_k, performance);


    return 0;
}