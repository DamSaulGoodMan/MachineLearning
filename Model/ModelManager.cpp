//
// Created by user on 17/02/2020.
//

#include "ModelManager.h"


ModelManager* ModelManager::INSTANCE = new ModelManager();

ModelManager::ModelManager()
{
    INSTANCE = this;
    modelStore = nullptr;
}


ModelManager* ModelManager::getModelManager()
{
    return INSTANCE;
}

void ModelManager::addNewModel(Model* model)
{
    //if(modelStore != nullptr) delete modelStore;
    modelStore = model;
}

bool ModelManager::removeModel(Model *model)
{
//    if(modelStore != nullptr)
//    {
//        delete modelStore;
//        return true;
//    }

    return false;
}