//
// Created by user on 17/02/2020.
//

#include <random>
#include <iostream>
#include <eigen3/Eigen/Dense>
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

void ModelLinear::regress(double inputs[], int nbOfInputsPackets, double predictState[], double trainigStep, int epoch)
{
    // INIT
    int packetSize = 2;
    Eigen::MatrixXd X(nbOfInputsPackets, packetSize + 1);
    Eigen::MatrixXd Y(nbOfInputsPackets, 1);

    for (int i = 0, j = 0; i < nbOfInputsPackets * packetSize; i += packetSize, j++) {
        X(j, 0) = 1;
        X(j, 1) = inputs[i];
        X(j, 2) = inputs[i + 1];
    }

    for (int i = 0; i < nbOfInputsPackets; i++) {
        Y(i, 0) = predictState[i];
    }

    // Do the regression
    Eigen::MatrixXd XTranspose = X.transpose();
    Eigen::MatrixXd result = ((XTranspose * X).inverse() * XTranspose) * Y;

    // Apply result to weight
    for(int i = 0; i < nbOfInputsPackets; i++) {
        weights[i] = result(i, 0);
    }
}

void ModelLinear::train(double* valuesOfEntry, int exempleNumber, double predictState[], double trainingStep, int epoch)
{
    for(int cnt = 0; cnt < epoch; cnt++)
    {
        int pickedTraining = rand() % exempleNumber;
        double* trainingParamsPointer = valuesOfEntry + (pickedTraining * (exempleNumber - 1));

        double modification = (double)trainingStep * (predictState[pickedTraining] - predict(trainingParamsPointer));
        weights[0] += modification;

        for(int cnt1 = 0; cnt1 < weightsNum - 1; cnt1++)
        {
            weights[cnt1 + 1] += modification * trainingParamsPointer[cnt1];
        }
    }
}

double ModelLinear::predictRegression(double *entry)
{
    double sum = weights[0];

    for(int i = 0; i < weightsNum - 1; i++)
    {
        sum += entry[i] * weights[i + 1];
    }

    return sum;
}

double ModelLinear::predict(double *entry)
{
    return ((predictRegression(entry) < 0) ? -1 : 1);
}

ModelLinear::~ModelLinear()
{
    delete[] weights;
}
