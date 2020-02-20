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
    for(int cnt = 0; cnt < epoch; cnt++)
    {
        int pickedTraining = rand() % entryNumber;
        double* trainingParamsPointer = valuesOfEntry + (pickedTraining * (entryNumber - 1));

        std::cerr << "[ 0 ]" << std::endl;

        predict(trainingParamsPointer);

        std::cerr << "[ 1 ]" << std::endl;

        double* delta[numOfLayer];
        for (int cnt1 = 0; cnt1 < numOfLayer; cnt1++)
        {
            std::cerr << "[ 1.0 ] delta[" << cnt << "][" << neuronesInLayer[cnt1] + 1 << "]" << std::endl;
            delta[cnt1] = new double[neuronesInLayer[cnt1] + 1];
        }

        std::cerr << "[ 2 ]" << std::endl;

        for (int cnt1 = 0; cnt1 < neuronesInLayer[numOfLayer - 1] + 1; cnt1++)
        {
            delta[0][numOfLayer - 1] = (1 - pow(neurones[numOfLayer - 1][cnt1], 2)) *
                    ((neurones[numOfLayer - 1][cnt1]) - predictState[pickedTraining]);
        }

        std::cerr << "[ 3 ]" << std::endl;

        for (int cnt1 = numOfLayer - 2; cnt1 >= 0; cnt1--)
        {
            std::cerr << "[ 3.0 ]" << std::endl;
            for (int cnt2 = 0; cnt2 < neuronesInLayer[cnt1] + 1; cnt2++)
            {
                std::cerr << "[ 3.1 ] cnt1=" << cnt1 << " && cnt2=" << cnt2 << std::endl;
                std::cerr << "[ 3.1 ] neuronesInLayer[cnt1 + 1]=" << neuronesInLayer[cnt1 + 1] << std::endl;
                for (int cnt3 = 1; cnt3 < neuronesInLayer[cnt1 + 1] + 1; cnt3++)
                {
                    //if(cnt3 == 1) delta[cnt1][cnt2] = 0;
                    std::cerr << "[ 3.2 ] cnt3=" << cnt3 << std::endl;
                    std::cerr << "[ 3.2 ] cnt1=" << cnt1 << " && cnt2=" << cnt2 << std::endl;
                    std::cerr << "[ 3.2 ] delta[" << cnt1 << "][" << cnt2 << "]=" << delta[cnt1][cnt2] << std::endl;

//                    if(cnt1 + 1 == 1 && cnt2 == 3 && cnt3 == 0) {
//                        std::cerr << " TEST : weight[1][3][0] =" << weight[1][3][0] << std::endl;
//                        return;
//                    }
                    delta[cnt1][cnt2] += (weight[cnt1 + 1][cnt2][cnt3] * delta[cnt1][cnt2]);
                }
                delta[cnt1][cnt2] *= (1 - pow(neurones[cnt1][cnt2], 2));
            }
        }

        std::cerr << "[ 4 ]" << std::endl;

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

        for (int cnt1 = 0; cnt < numOfLayer; cnt1++)
        {
            delete[] delta[cnt1];
        }
    }
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
        for (int cnt2 = 0; cnt2 < neuronesInLayer[cnt1]; cnt2++)
        {
            for (int cnt3 = 0; cnt3 < neuronesInLayer[cnt1 - 1]; cnt3++)
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