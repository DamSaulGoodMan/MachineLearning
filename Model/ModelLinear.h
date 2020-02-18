//
// Created by user on 17/02/2020.
//

#ifndef MACHINELEARNING_MODELLINEAR_H
#define MACHINELEARNING_MODELLINEAR_H


#include "Model.h"


class ModelLinear : public Model
{
public:
    explicit ModelLinear(int dimInputNumber);

    void train(double valuesOfEntry[], int entryNumber, double predictState[], double trainingStep, int epoch) override;
    int predict(double *params) override;

private:
    int weightsNum;
    double* weights;
};


#endif //MACHINELEARNING_MODELLINEAR_H
