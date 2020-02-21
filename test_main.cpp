//
// Created by user on 18/02/2020.
//

#include <iostream>
#include "Model/ModelLinear.h"
#include "Model/ModelManager.h"
#include "Model/ModelMultiLayers.h"


using namespace std;

void hugoTest();

void predictAll(ModelLinear* model) {
    for(double i = -7; i < 8; i += 1) {
        for(double j = 0; j < 15; j += 1) {
            double params[] = {i, j};
            int predicted = model->predict(params);
            std::cout << (predicted == 0 ? "0" : predicted >= 1 ? "+" : "-");
        }

        std::cout << std::endl;
    }
}

void predictAllRegress(ModelLinear* model) {
    for(double i = -7; i < 8; i += 1) {
        for(double j = 0; j < 15; j += 1) {
            double params[] = {i, j};
            int predicted = model->predictRegression(params);
            std::cout << (predicted == 0 ? "0" : predicted >= 1 ? "+" : "-");
        }

        std::cout << std::endl;
    }
}

void hugoTest()
{
    auto modelLi = new ModelLinear(2);
    double trainingParams[] = {-3, 9, 6, 13, -7, 2};
    double trainingResults[] = {1, 1, -1};
    // modelLi->train(trainingParams, 3, trainingResults, 0.0001, 10000);
    modelLi->regress(trainingParams, 3, trainingResults);
    predictAllRegress(modelLi);
    delete modelLi;
}

void damTest();

int main()
{
    //hugoTest();
    damTest();
}

void damTest()
{
    int neuronesPerLayers[2] = {2, 1};
    auto modelLi = new ModelMultiLayers(2, neuronesPerLayers);
    double trainingParams[] = {-1, -1, 1, 1, -1, 1, 1, -1};
    double trainingResults[] = {1, -1, 1, -1};

    modelLi->train(trainingParams, 4, trainingResults, 0.01, 10000);

    std::cout << modelLi->predict(trainingParams) << std::endl;
    std::cout << modelLi->predict(trainingParams+2) << std::endl;
    std::cout << modelLi->predict(trainingParams+4) << std::endl;
    std::cout << modelLi->predict(trainingParams+6) << std::endl;
    //delete modelLi;
}
