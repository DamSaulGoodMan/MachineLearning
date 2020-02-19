//
// Created by user on 17/02/2020.
//

#include <random>
#include <iostream>
#include "ModelLinear.h"
#include "../Commun.h"


using namespace std;


ModelLinear::ModelLinear(int dimInputNumber)
    : Model(dimInputNumber, 1)
{
    weightsNum = dimInputNumber + 1;
    weights = new double[weightsNum];

    for (int cnt = 0; cnt < weightsNum; cnt++)
    {
        weights[cnt] = Commun::fRand(-1.0f, 1.0f);
    }
}

void ModelLinear::train(double* valuesOfEntry, int exempleNumber, double predictState[], double trainingStep, int epoch)
{
    for(int cnt = 0; cnt < epoch; cnt++)
    {
        int pickedTraining = rand() % exempleNumber;
//        cerr << "pickedTraining=" << pickedTraining << " rand()=" << rand() << endl;

        double* trainingParamsPointer = valuesOfEntry + (pickedTraining * (exempleNumber - 1));
//        cerr << "case = " << pickedTraining * (entryNumber - 1) << endl;
//        cerr << "ptr = " << trainingParamsPointer << endl;

        double modification = (double)trainingStep * (predictState[pickedTraining] - predict(trainingParamsPointer));
        weights[0] += modification;

        for(int cnt1 = 0; cnt1 < weightsNum - 1; cnt1++)
        {
            weights[cnt1 + 1] += modification * trainingParamsPointer[cnt1];
        }
    }
}

int ModelLinear::predict(double *entry)
{
    double sum = weights[0];
    for(int i = 0; i < weightsNum - 1; i++)
    {
        sum += entry[i] * weights[i + 1];
    }

    int result = ((sum < 0) ? -1 : 1);
    return result;
}

ModelLinear::~ModelLinear()
{
    delete[] weights;
}
