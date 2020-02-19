#include "API.h"
#include "../Model/ModelManager.h"
#include "../Model/ModelMultiLayers.h"

#include <iostream>

using namespace std;

extern "C"
{
EXPORTED ModelMultiLayers* createMultiLayersModel(int numOfLayer, int neuronesInLayer[])
{
    auto model = new ModelMultiLayers(numOfLayer, neuronesInLayer);

    ModelManager::getModelManager()->addNewModel(model);

    return model;
}

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

EXPORTED void regressModel(Model* model, double inputs[], int nbOfInputsPackets, double predictState[])
{
    model->regress(inputs, nbOfInputsPackets, predictState);
}

EXPORTED double predict(Model* model, double params[])
{
    return model->predict(params);
}

EXPORTED double predictRegression(Model* model, double params[])
{
    return model->predictRegression(params);
}

EXPORTED bool removeModel(Model* model)
{
    return ModelManager::getModelManager()->removeModel(model);
}

}

