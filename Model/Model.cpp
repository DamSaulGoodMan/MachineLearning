//
// Created by user on 17/02/2020.
//

#include "Model.h"


Model::Model(int dimInputNumber, int dimOutputNumber)
{
    input = new double[dimInputNumber + 1];
    output = new double[dimOutputNumber + 1];
}