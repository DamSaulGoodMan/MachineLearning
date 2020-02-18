//
// Created by user on 17/02/2020.
//

#include <random>
#include <iostream>
#include "ModelLinear.h"


using namespace std;


ModelLinear::ModelLinear(int dimInputNumber)
    : Model(dimInputNumber, 1)
{
    weightsNum = dimInputNumber + 1;
    weights = new double[weightsNum];

    for (int cnt = 0; cnt < weightsNum; cnt++)
    {
        weights[cnt] = ((rand() % 2) ? 1 : -1);
    }
}

void ModelLinear::train(double valuesOfEntry[], int entryNumber, double predictState[], double trainingStep, int epoch)
{
    for(int cnt = 0; cnt < epoch; cnt++)
    {
        int initWeight = ((rand() % 2) ? 1 : -1);
        int pickedTraining = floor(initWeight * entryNumber);

        int trainingParamsPosition = weightsNum * pickedTraining;
        double modification = (double)trainingStep * (predictState[pickedTraining] - predict(&valuesOfEntry[trainingParamsPosition]));
        weights[0] += modification;

        for(int cnt1 = 0; cnt1 < weightsNum; cnt1++)
        {
            weights[cnt1 + 1] += modification * valuesOfEntry[trainingParamsPosition + cnt1];
        }
    }
}

int ModelLinear::predict(double *entry)
{
    double sum = weights[0];
    for(int i = 0; i < weightsNum; i++)
    {
        sum += entry[i] * weights[i + 1];
    }

    int result = ((sum < 0) ? -1 : 1);
    return result;
}