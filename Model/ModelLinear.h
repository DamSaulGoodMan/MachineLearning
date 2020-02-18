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

    void train(int entryNumber, const double predictState[], double trainingParams[], double trainingStep, int epoch);
    int predict(double *params);

private:
    int weightsNum;
    double* weights;
};


#endif //MACHINELEARNING_MODELLINEAR_H
