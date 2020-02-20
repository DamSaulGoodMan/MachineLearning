//
// Created by user on 18/02/2020.
//

#include <random>
#include "ModelMultiLayers.h"
#include "../Commun.h"
#include <math.h>
#include <iostream>


ModelMultiLayers::ModelMultiLayers(int numOfLayer, int neuronesInLayer[])
     : Model(neuronesInLayer[0], neuronesInLayer[numOfLayer - 1]),
        numOfLayer(numOfLayer), neuronesInLayer(neuronesInLayer)
{
    neurones = new double*[numOfLayer];
    weight = new double**[numOfLayer];

    for (int cnt = 0; cnt < numOfLayer; cnt++)
    {
        neurones[cnt] = new double[neuronesInLayer[cnt] + 1];
        neurones[cnt][0] = 1;

        if(cnt > 0)
        {
            weight[cnt] = new double*[neuronesInLayer[cnt]];
            // TODO change I and J
            for (int cnt1 = 0; cnt1 < neuronesInLayer[cnt] + 1; cnt1++)
            {
                weight[cnt][cnt1] = new double[neuronesInLayer[cnt - 1]];
                for (int cnt2 = 0; cnt2 < neuronesInLayer[cnt - 1] + 1; cnt2++)
                {
                    weight[cnt][cnt1][cnt2 - 1] = Commun::fRand(-1.0f, 1.0f);
                    std::cerr << "[ Weight ] [" << cnt << "][" << cnt1 << "][" << cnt2 << "]" << std::endl;
                }
            }
        }
    }


//    std::cerr << " TEST : weight dim = " << numOfLayer - 1 << neuronesInLayer[numOfLayer - 2] + 1 << neuronesInLayer[numOfLayer - 1] << std::endl;
//    weight[3][3][1] = 1;
//    std::cerr << "LLLAAAA" << std::endl;
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

        for (int cnt1 = 0; cnt1 < neuronesInLayer[numOfLayer - 1] + 1; cnt1++)
        {
            std::cerr << numOfLayer << std::endl;
            delta[numOfLayer - 1][cnt1] = (1 - pow(neurones[numOfLayer - 1][cnt1], 2)) *
                    ((neurones[numOfLayer - 1][cnt1]) - predictState[pickedTraining]);
        }

        for (int l = numOfLayer - 2; l >= 0; l--)
        {
            for (int i = 0; i < neuronesInLayer[l] + 1; i++)
            {
                std::cerr << "neuronesInLayer[" << l << "] + 1=" << neuronesInLayer[l] + 1 << std::endl;
                delta[l][i] = 0;
                for (int j = 1; j < neuronesInLayer[l + 1] + 1; j++)
                {
                    std::cerr << "weight[" << l + 1 << "][" << i << "][" << j << "]=" << weight[l + 1][i][j] << std::endl;
                    std::cerr << "delta[l + 1][j]=" << delta[l + 1][j] << std::endl;
                    delta[l][i] += weight[l + 1][i][j] * delta[l + 1][j];
                }
                delta[l][i] *= 1 - pow(neurones[l][i], 2);
            }
        }

        for (int cnt1 = 1; cnt1 < numOfLayer; cnt1++)
        {
            std::cerr << "[ 4.0 ]" << std::endl;
            for (int cnt2 = 0; cnt2 < neuronesInLayer[cnt1] + 1; cnt2++)
            {
                std::cerr << "[ 4.1 ]" << std::endl;
                for (int cnt3 = 0; cnt3 < neuronesInLayer[cnt1 - 1] + 1; cnt3++)
                {
                    std::cerr << "[ 4.2 ] [" << cnt1 << "][" << cnt2 << "][" << cnt3 << "]" << std::endl;
                    std::cerr << "weight[cnt1][cnt2][cnt3]=" <<  weight[cnt1][cnt2][cnt3] << std::endl;
                    weight[cnt1][cnt2][cnt3] -= trainingStep * neurones[cnt1 - 1][cnt2] * delta[cnt1][cnt2];
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
    for(int cnt1 = 1; cnt1 < neuronesInLayer[0]; cnt1++)
    {
        neurones[0][cnt1] = entry[cnt1 - 1];
    }

    // odl : "cnt1 < numOfLayer - 1;" Why - 1 ??
    for (int cnt1 = 1; cnt1 < numOfLayer; cnt1++)
    {
        for (int cnt2 = 1; cnt2 < neuronesInLayer[cnt1] + 1; cnt2++)
        {
            for (int cnt3 = 0; cnt3 < neuronesInLayer[cnt1 - 1] + 1; cnt3++)
            {
                neurones[cnt1][cnt2] += weight[cnt1][cnt2][cnt3] * neurones[cnt1 - 1][cnt2];
            }
            neurones[cnt1][cnt2] = tanh(neurones[cnt1][cnt2]);
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