#include "API.h"
#include "../Model/ModelManager.h"

#include <iostream>

using namespace std;

extern "C"
{

EXPORTED ModelLinear* createLinearModel(int dimInputNumber, int dimOutputNumber)
{
    auto model = new ModelLinear(dimInputNumber);

    ModelManager::getModelManager()->addNewModel(model);

    return model;
}

EXPORTED void trainModel(Model* model, double valuesOfEntry[], int entryNumber,
        double predictState[], double trainingStep, int epoch)
{
    model->train(valuesOfEntry, entryNumber, predictState, trainingStep, epoch);
}

EXPORTED int predict(Model* model, double params[], int numParam)
{
    return model->predict(params);
}

EXPORTED bool removeModel(Model* model)
{
    return ModelManager::getModelManager()->removeModel(model);
}

}

