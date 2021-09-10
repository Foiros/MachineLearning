#include <iostream>
#include "DataHandler.h"

int main() {

    auto* dh = new DataHandler();
    dh->ReadFeatureVector("../train-images-idx3-ubyte");
    dh->ReadFeatureLabels("../train-labels-idx1-ubyte");
    dh->SplitData();
    dh->CountClasses();
    return 0;
}
