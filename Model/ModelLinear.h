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

    void regress(double inputs[], int nbOfInputsPackets, double predictState[]) override;
    void train(double valuesOfEntry[], int entryNumber, double predictState[], double trainingStep, int epoch) override;
    double predict(double *params) override;
    double predictRegression(double *params) override;

    virtual ~ModelLinear();

private:
    int weightsNum;
    double* weights;
};


#endif //MACHINELEARNING_MODELLINEAR_H
