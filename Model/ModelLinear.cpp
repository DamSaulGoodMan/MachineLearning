//
// Created by user on 17/02/2020.
//

#include <random>
#include <iostream>
#include "ModelLinear.h"


ModelLinear::ModelLinear(int dimInputNumber)
    : Model(dimInputNumber, 1)
{
    weightsNum = dimInputNumber + 1;
    weights = new double[weightsNum];

    std::random_device rd;

    for (int cnt = 0; cnt < weightsNum; cnt++)
    {
        weights[cnt] = ((rd() % 2) ? 1 : -1);
    }
}

void ModelLinear::train(double valuesOfEntry[], int entryNumber, double predictState[], double trainingStep, int epoch)
{
    for(int cnt = 0; cnt < epoch; cnt++)
    {
        std::random_device rd;
        int initWeight = ((rd() % 2) ? 1 : -1);
        int pickedTraining = floor(initWeight * entryNumber);

        int trainingParamsPosition = weightsNum * pickedTraining;
        double modification = (double)trainingStep * (predictState[pickedTraining] - predict(&valuesOfEntry[trainingParamsPosition]));
        weights[0] += modification;

        for(int cnt2 = 0; cnt2 < weightsNum; cnt2++)
        {
            weights[cnt2 + 1] += modification * valuesOfEntry[trainingParamsPosition + cnt2];
        }
    }
}

int ModelLinear::predict(double *params)
{
    double sum = weights[0];
    for(int i = 0; i < weightsNum; i++)
    {
        sum += params[i] * weights[i + 1];
    }

    int result = ((sum < 0) ? -1 : 1);
    return result;
}