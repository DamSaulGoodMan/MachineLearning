//
// Created by user on 17/02/2020.
//

#ifndef MACHINELEARNING_MODELMANAGER_H
#define MACHINELEARNING_MODELMANAGER_H


#include "Model.h"

#include <vector>


class ModelManager
{
public:
    ModelManager();

    static ModelManager* getModelManager();

    void addNewModel(Model* model);
    bool removeModel(Model* model);

private:
    static ModelManager* INSTANCE;

    Model* modelStore;
};


#endif //MACHINELEARNING_MODELMANAGER_H
