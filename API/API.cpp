#include "API.h"
#include "../Model/ModelManager.h"

#include <iostream>


extern "C"
{

EXPORTED ModelLinear* createLinearModel(int entryNumber)
{
    auto model = new ModelLinear(entryNumber);

    ModelManager::getModelManager()->addNewModel(model);
}

EXPORTED void trainLinearModel(ModelLinear* modelLinear, double valuesOfEntry[], int entryNumber, bool predictState[])
{

}

EXPORTED bool predict(Model* model)
{

}

}

