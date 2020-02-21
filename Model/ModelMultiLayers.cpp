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
        numOfLayer(numOfLayer), neuronesInLayer(neuronesInLayer)
{
    neurones = new double*[numOfLayer];
    weight = new double**[numOfLayer];

    for (int l = 0; l < numOfLayer; l++)
    {
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
                    std::cerr << "[ Weight ] [" << l << "][" << j << "][" << i << "]" << std::endl;
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
        double* trainingParamsPointer = valuesOfEntry + (pickedTraining * (entryNumber - 1));

        predict(trainingParamsPointer);

        for (int i = 0; i < neuronesInLayer[numOfLayer - 1] + 1; i++)
        {
            delta[numOfLayer - 1][i] = (1 - pow(neurones[numOfLayer - 1][i], 2)) *
                                       ((neurones[numOfLayer - 1][i]) - predictState[pickedTraining]);
        }

        for (int l = numOfLayer - 2; l >= 0; l--)
        {
            for (int i = 0; i < neuronesInLayer[l] + 1; i++)
            {
                std::cerr << "neuronesInLayer[" << l << "] + 1=" << neuronesInLayer[l] + 1 << std::endl;
                delta[l][i] = 0;
                for (int j = 1; j < neuronesInLayer[l + 1] + 1; j++)
                {
                    std::cerr << "weight[" << l + 1 << "][" << i << "][" << j << "]=" << weight[l + 1][j][i] << std::endl;
                    std::cerr << "delta[l + 1][j]=" << delta[l + 1][j] << std::endl;
                    delta[l][i] += weight[l + 1][j][i] * delta[l + 1][j];
                }
                delta[l][i] *= 1 - pow(neurones[l][i], 2);
            }
        }

        for (int l = 1; l < numOfLayer; l++)
        {
            std::cerr << "[ 4.0 ]" << std::endl;
            for (int j = 0; j < neuronesInLayer[l] + 1; j++)
            {
                std::cerr << "[ 4.1 ]" << std::endl;
                for (int i = 0; i < neuronesInLayer[l - 1] + 1; i++)
                {
                    std::cerr << "[ 4.2 ] [" << l << "][" << j << "][" << i << "]" << std::endl;
                    std::cerr << "weight[l][j][i]=" << weight[l][j][i] << std::endl;
                    weight[l][j][i] -= trainingStep * neurones[l - 1][i] * delta[l][j];
                }
            }
        }
        std::cerr << "[ 5 ]" << std::endl;
    }

    for (int cnt1 = 0; cnt1 < numOfLayer; cnt1++)
    {
        delete[] delta[cnt1];
    }
    delete[] delta;
}

void ModelMultiLayers::regress(double inputs[], int nbOfInputsPackets, double predictState[]) {}

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
            for (int i = 0; i < neuronesInLayer[l - 1] + 1; i++)
            {
                neurones[l][j] += weight[l][j][i] * neurones[l - 1][i];
            }
            neurones[l][j] = tanh(neurones[l][j]);
        }
    }

    return (neurones[numOfLayer - 1][1] < 0) ? -1 : 1;
}


double ModelMultiLayers::predictRegression(double *entry)
{

    return 0;
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