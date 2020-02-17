//
// Created by user on 17/02/2020.
//

#ifndef MACHINELEARNING_MODELLINEAR_H
#define MACHINELEARNING_MODELLINEAR_H


#include "Model.h"


class ModelLinear : public Model
{
public:
    explicit ModelLinear(int entryNumber);

private:
    double* entry;
};


#endif //MACHINELEARNING_MODELLINEAR_H
