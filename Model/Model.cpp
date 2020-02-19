//
// Created by user on 17/02/2020.
//

#include <iostream>
#include "Model.h"


Model::Model(int dimInputNumber, int dimOutputNumber)
{
    input = new double[dimInputNumber + 1];
    output = new double[dimOutputNumber + 1];
}

Model::~Model()
{
    std::cout << "~Model()" << std::endl;
}

