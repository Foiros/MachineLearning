cmake_minimum_required(VERSION 3.20)
project(MachineLearning)

set(CMAKE_CXX_STANDARD 20)

add_executable(MachineLearning main.cpp Data.cpp Data.h DataHandler.cpp DataHandler.h KNN.cpp KNN.h Common_Data.cpp Common_Data.h KMean.cpp KMean.h Layer.cpp Layer.h InputLayer.cpp InputLayer.h HiddenLayer.cpp HiddenLayer.h OutputLayer.cpp OutputLayer.h Neuron.cpp Neuron.h Network.cpp Network.h)
