//
// Created by hugo on 19/02/2020.
//

#ifndef MACHINELEARNING_RBFNAIVE_H
#define MACHINELEARNING_RBFNAIVE_H


#include "Model.h"


class RBFNaive : public Model
{
public:
    RBFNaive(int dimInputNumber, double gamma);

    void regress(double inputs[], int nbOfInputsPackets, double predictState[]) override;
    void train(double valuesOfEntry[], int entryNumber, double predictState[], double _, int epoch) override;
    double predict(double *params) override;
    double predictRegression(double *params) override;

    virtual ~RBFNaive();

private:
    int weightsNum;
    double gamma;
    double* weights;

    double getRBFValue(double x1, double y1, double x2, double y2);
};

#endif //MACHINELEARNING_RBFNAIVE_H
