#include "API.h"
#include "../Model/ModelManager.h"

#include <iostream>


extern "C"
{

EXPORTED ModelLinear* createLinearModel(int dimInputNumber, int dimOutputNumber)
{
    auto model = new ModelLinear(dimInputNumber);

    ModelManager::getModelManager()->addNewModel(model);

    return model;
}

EXPORTED void trainLinearModel(ModelLinear* modelLinear, double valuesOfEntry[], int entryNumber,
        double predictState[], double trainingStep, int epoch)
{
    modelLinear->train(entryNumber, predictState, valuesOfEntry, trainingStep, epoch);
}

EXPORTED int predict(ModelLinear* model, double params[], int numParam)
{
    return model->predict(params);
}

EXPORTED int removeModel(Model* model, double params[], int numParam)
{

}

}

