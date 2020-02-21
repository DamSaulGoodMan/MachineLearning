//
// Created by hugo on 19/02/2020.
//

#include "RBFNaive.h"
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <math.h>
#include "../Commun.h"

using namespace std;

RBFNaive::RBFNaive(int dimInputNumber, double gamma)
        : Model(dimInputNumber, 1)
{
    weightsNum = dimInputNumber + 1;
    weights = new double[weightsNum];

    for (int cnt = 0; cnt < weightsNum; cnt++)
    {
        weights[cnt] = Commun::fRand(-1.0f, 1.0f);
    }

    this->gamma = gamma;
}

void RBFNaive::regress(double inputs[], int nbOfInputsPackets, double predictState[], double trainigStep, int epoch)
{

}

double euclidianDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double RBFNaive::getRBFValue(double x1, double y1, double x2, double y2) {
   return exp(-gamma * pow(euclidianDistance(x1, y1, x2, y2), 2));
}

void RBFNaive::train(double inputs[], int nbOfInputsPackets, double predictState[], double _, int epochs)
{
    int packetSize = 2;
    Eigen::MatrixXd phi(nbOfInputsPackets, nbOfInputsPackets);
    Eigen::MatrixXd Y(nbOfInputsPackets, 1);

    for (int currentEpoch = 0; currentEpoch < epochs; currentEpoch++) {
        for (int i = 0, j = 0; i < nbOfInputsPackets * packetSize; i += packetSize, j++) {
            for (int k = 0, l = 0; k < nbOfInputsPackets * packetSize; k += packetSize, l++) {
                phi(j, l) += getRBFValue(inputs[i], inputs[i + 1], inputs[k], inputs[k + 1]);
            }
        }

        for (int i = 0; i < nbOfInputsPackets; i++) {
            Y(i, 0) += predictState[i];
        }

        auto result = phi.inverse() * Y;

        for(int i = 0; i < nbOfInputsPackets; i++) {
            weights[i] += result(i, 0);
        }
    }
}

double RBFNaive::predictRegression(double *x) {
    double sum = 0;

    for(int i = 0; i < weightsNum; i++) {
        for (int j = 0; j < weightsNum; j++) {
            sum += weights[i] * getRBFValue(x[i], x[i + 1], x[j], x[j + 1]);
        }
    }

    return sum;
}

double RBFNaive::predict(double *entry)
{
    return (predictRegression(entry) < 0) ? -1 : 1;
}

RBFNaive::~RBFNaive()
{
    delete[] weights;
}

