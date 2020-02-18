//
// Created by user on 17/02/2020.
//

#include "ModelManager.h"


ModelManager* ModelManager::INSTANCE = new ModelManager();

ModelManager::ModelManager()
{
    INSTANCE = this;
}


ModelManager* ModelManager::getModelManager()
{
    return INSTANCE;
}

void ModelManager::addNewModel(Model* model)
{
    modelStore.push_back(model);
}

void ModelManager::removeModel(Model *model)
{
    for (auto iterator = modelStore.begin(); iterator != modelStore.end(); ++iterator)
    {
        if((*iterator) == model)
        {
            modelStore.erase(iterator);
            break;
        }
    }
}
