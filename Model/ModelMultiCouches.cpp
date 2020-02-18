//
// Created by user on 18/02/2020.
//

#include <random>
#include "ModelMultiCouches.h"


ModelMultiCouches::ModelMultiCouches(int dimInputNumber,
                                     int dimOutputNumber,
                                     int numOfDeepLayer,
                                     int neuronesInDeepLayer[])
     : Model(dimInputNumber, dimOutputNumber),
        numOfDeepLayer(numOfDeepLayer), neuronesInDeepLayer(neuronesInDeepLayer)
{
    neurones = new double*[numOfDeepLayer + 2];
    weight = new double**[numOfDeepLayer + 1];

    neurones[0] = new double[dimInputNumber + 1];
    weight[0] = new double*[dimInputNumber + 1];
    for (int cnt = 0; cnt < dimInputNumber + 1; cnt++)
    {
        weight[0][cnt] = new double[neuronesInDeepLayer[0] + 1];

        for (int cnt1 = 0; cnt1 < neuronesInDeepLayer[0] + 1; cnt1++)
        {
            weight[0][cnt][cnt1] = ((rand() % 2) ? 1 : -1);
        }
    }

    for (int cnt = 0; cnt < numOfDeepLayer - 1; cnt++)
    {
        weight[cnt + 1] = new double*[neuronesInDeepLayer[cnt] + 1];
        for (int cnt1 = 0; cnt1 < neuronesInDeepLayer[cnt] + 1; cnt1++)
        {
            weight[cnt + 1][cnt1] = new double[neuronesInDeepLayer[cnt + 1] + 1];

            for (int cnt2 = 0; cnt2 < neuronesInDeepLayer[cnt + 1] + 1; cnt2++)
            {
                weight[cnt + 1][cnt1][cnt2] = ((rand() % 2) ? 1 : -1);
            }
        }
    }

    neurones[numOfDeepLayer + 1] = new double[dimOutputNumber + 1];
    weight[numOfDeepLayer] = new double*[neuronesInDeepLayer[numOfDeepLayer - 1] + 1];

    for (int cnt = 0; cnt < dimOutputNumber + 1; cnt++)
    {
        weight[numOfDeepLayer][cnt] = new double[dimOutputNumber + 1];

        for (int cnt1 = 0; cnt1 < dimOutputNumber + 1; cnt1++)
        {
            weight[numOfDeepLayer][cnt][cnt1] = ((rand() % 2) ? 1 : -1);
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

        }
    }
}

int ModelMultiCouches::predict(double *entry)
{
    return 0;
}
