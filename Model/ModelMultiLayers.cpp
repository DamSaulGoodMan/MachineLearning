//
// Created by user on 18/02/2020.
//

#include <random>
#include "ModelMultiLayers.h"
#include "../Commun.h"
#include <cmath>
#include <iostream>


ModelMultiLayers::ModelMultiLayers(int numOfLayer, int neuronesInLayer[])
     : Model(neuronesInLayer[0], neuronesInLayer[numOfLayer - 1]),
        numOfLayer(numOfLayer)
{
    neurones = new double*[numOfLayer];
    weight = new double**[numOfLayer];
    this->neuronesInLayer = new int[numOfLayer];



    for (int l = 0; l < numOfLayer; l++)
    {
        this->neuronesInLayer[l] = neuronesInLayer[l];
        neurones[l] = new double[neuronesInLayer[l] + 1];
        neurones[l][0] = 1;

        if(l > 0)
        {
            weight[l] = new double*[neuronesInLayer[l] + 1];
            for (int j = 0; j < neuronesInLayer[l] + 1; j++)
            {
                weight[l][j] = new double[neuronesInLayer[l - 1] + 1];
                for (int i = 0; i < neuronesInLayer[l - 1] + 1; i++)
                {
                    weight[l][j][i] = Commun::fRand(-1.0f, 1.0f);
                }
            }
        }
    }
}

void
ModelMultiLayers::train(double *valuesOfEntry, int entryNumber, double *predictState, double trainingStep, int epoch)
{

    double** delta = new double*[numOfLayer];
    for (int cnt1 = 0; cnt1 < numOfLayer; cnt1++)
    {
        delta[cnt1] = new double[neuronesInLayer[cnt1] + 1];
    }

    for(int cnt = 0; cnt < epoch; cnt++)
    {
        int pickedTraining = rand() % entryNumber;
        double* trainingParamsPointer = valuesOfEntry + (pickedTraining * neuronesInLayer[0]);

        predict(trainingParamsPointer);

        for (int i = 1; i < neuronesInLayer[numOfLayer - 1] + 1; i++)
        {
            delta[numOfLayer - 1][i] = (1 - pow(neurones[numOfLayer - 1][i], 2)) *
                                       ((neurones[numOfLayer - 1][i]) - predictState[pickedTraining]);
        }

        for (int l = numOfLayer - 2; l >= 0; l--)
        {
            for (int i = 1; i < neuronesInLayer[l] + 1; i++)
            {
                delta[l][i] = 0;
                for (int j = 1; j < neuronesInLayer[l + 1] + 1; j++)
                {
                    delta[l][i] += weight[l + 1][j][i] * delta[l + 1][j];
                }
                delta[l][i] *= 1 - pow(neurones[l][i], 2);
            }
        }

        for (int l = 1; l < numOfLayer; l++)
        {
            for (int j = 1; j < neuronesInLayer[l] + 1; j++)
            {
                for (int i = 0; i < neuronesInLayer[l - 1] + 1; i++)
                {
                    weight[l][j][i] -= trainingStep * neurones[l - 1][i] * delta[l][j];
                }
            }
        }
    }

    for (int cnt1 = 0; cnt1 < numOfLayer; cnt1++)
    {
        delete[] delta[cnt1];
    }
    delete[] delta;
}

void ModelMultiLayers::regress(double inputs[], int nbOfInputsPackets, double predictState[], double trainigStep, int epoch)
{
    double** delta = new double*[numOfLayer];
    for (int cnt1 = 0; cnt1 < numOfLayer; cnt1++)
    {
        delta[cnt1] = new double[neuronesInLayer[cnt1] + 1];
    }

    for(int cnt = 0; cnt < epoch; cnt++)
    {
        int pickedTraining = rand() % nbOfInputsPackets;
        double* trainingParamsPointer = inputs + (pickedTraining * neuronesInLayer[0]);

        predictRegression(trainingParamsPointer);

        for (int i = 1; i < neuronesInLayer[numOfLayer - 1] + 1; i++)
        {
            delta[numOfLayer - 1][i] = ((neurones[numOfLayer - 1][i]) - predictState[pickedTraining]);
        }

        for (int l = numOfLayer - 2; l >= 0; l--)
        {
            for (int i = 1; i < neuronesInLayer[l] + 1; i++)
            {
                delta[l][i] = 0;
                for (int j = 1; j < neuronesInLayer[l + 1] + 1; j++)
                {
                    delta[l][i] += weight[l + 1][j][i] * delta[l + 1][j];
                }
                delta[l][i] *= 1 - pow(neurones[l][i], 2);
            }
        }

        for (int l = 1; l < numOfLayer; l++)
        {
            for (int j = 1; j < neuronesInLayer[l] + 1; j++)
            {
                for (int i = 0; i < neuronesInLayer[l - 1] + 1; i++)
                {
                    weight[l][j][i] -= trainigStep * neurones[l - 1][i] * delta[l][j];
                }
            }
        }
    }

    for (int cnt1 = 0; cnt1 < numOfLayer; cnt1++)
    {
        delete[] delta[cnt1];
    }
    delete[] delta;
}

double ModelMultiLayers::predict(double *entry)
{
    for(int l = 1; l < neuronesInLayer[0] + 1; l++)
    {
        neurones[0][l] = entry[l - 1];
    }

    for (int l = 1; l < numOfLayer; l++)
    {
        for (int j = 1; j < neuronesInLayer[l] + 1; j++)
        {
            neurones[l][j] = 0;
            for (int i = 0; i < neuronesInLayer[l - 1] + 1; i++)
            {
                neurones[l][j] += weight[l][j][i] * neurones[l - 1][i];
            }
            neurones[l][j] = tanh(neurones[l][j]);
        }
    }

    return neurones[numOfLayer - 1][1];// (neurones[numOfLayer - 1][1] < 0) ? -1 : 1;
}


double ModelMultiLayers::predictRegression(double *entry)
{
    return predict(entry);
}

ModelMultiLayers::~ModelMultiLayers()
{
    for (int cnt = 0; cnt < numOfLayer + 2; cnt++)
    {
        delete[] neurones[cnt];
    }
    delete[] neurones;

    for (int cnt = 0; cnt < numOfLayer - 1; cnt++)
    {
        for (int cnt1 = 0; cnt1 < neuronesInLayer[cnt] + 1; cnt1++)
        {
            delete[] weight[cnt][cnt1];
        }
        delete[] weight[cnt];
    }
    delete[] weight;
}