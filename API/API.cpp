#include "API.h"
#include "../Model/ModelManager.h"

#include <iostream>


extern "C"
{

EXPORTED ModelLinear* createLinearModel(int dimInputNumber, int dimOutputNumber)
{
    auto model = new ModelLinear(dimInputNumber, dimOutputNumber);

    ModelManager::getModelManager()->addNewModel(model);
}

EXPORTED void trainLinearModel(ModelLinear* modelLinear, double valuesOfEntry[], int entryNumber,
        double predictState[], double trainingStep)
{

}

EXPORTED double predict(Model* model, double params[], int numParam)
{

}

}

