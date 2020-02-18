//
// Created by user on 18/02/2020.
//

#ifndef MACHINELEARNING_MODELMULTICOUCHES_H
#define MACHINELEARNING_MODELMULTICOUCHES_H


#include "Model.h"


class ModelMultiCouches : public Model
{
public:
    ModelMultiCouches(int dimInputNumber,
                      int dimOutputNumber,
                      int numOfDeepLayer,
                      int neuronesInDeepLayer[]);

    void train(double *valuesOfEntry, int entryNumber, double *predictState, double trainingStep, int epoch) override;

    int predict(double *entry) override;

private:
    int numOfDeepLayer;
    int* neuronesInDeepLayer;
    double** neurones;
    double*** weight;
};


#endif //MACHINELEARNING_MODELMULTICOUCHES_H
