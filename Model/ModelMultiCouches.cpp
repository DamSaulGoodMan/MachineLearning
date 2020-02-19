//
// Created by user on 18/02/2020.
//

#include <random>
#include "ModelMultiCouches.h"


ModelMultiCouches::ModelMultiCouches(int numOfLayer, int neuronesInLayer[])
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
            weight[cnt] = new double*[neuronesInLayer[cnt - 1] + 1];
            for (int cnt1 = 0; cnt1 < neuronesInLayer[cnt - 1] + 1; cnt1++)
            {
                weight[cnt][cnt1] = new double[neuronesInLayer[cnt] + 1];
                for (int cnt2 = 1; cnt2 < neuronesInLayer[cnt] + 1; cnt2++)
                {
                    weight[cnt][cnt1][cnt2] = ((rand() % 2) ? 1 : -1);
                }
            }
        }
    }
}

void
ModelMultiCouches::train(double *valuesOfEntry, int entryNumber, double *predictState, double trainingStep, int epoch)
{
    for(int cnt = 0; cnt < epoch; cnt++)
    {
        for (int cnt1 = 0; cnt1 < entryNumber; cnt1++)
        {
            neurones[0][cnt1] = valuesOfEntry[cnt1];
        }
    }
}

int ModelMultiCouches::predict(double *entry)
{

    return 0;
}

ModelMultiCouches::~ModelMultiCouches()
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
