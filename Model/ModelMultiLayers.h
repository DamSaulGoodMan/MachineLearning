//
// Created by user on 18/02/2020.
//

#ifndef MACHINELEARNING_MODELMULTILAYERS_H
#define MACHINELEARNING_MODELMULTILAYERS_H


#include "Model.h"


class ModelMultiLayers : public Model
{
public:
    ModelMultiLayers(int numOfLayer, int neuronesInDeepLayer[]);

    void train(double *valuesOfEntry, int entryNumber, double *predictState, double trainingStep, int epoch) override;

    double predict(double *entry) override;

    void regress(double inputs[], int nbOfInputsPackets, double predictState[], double trainigStep, int epoch) override;
    double predictRegression(double *entry) override;

    virtual ~ModelMultiLayers();

private:
    int numOfLayer;
    int* neuronesInLayer;
    double** neurones;
    double*** weight;
};


#endif //MACHINELEARNING_MODELMULTILAYERS_H
