//
// Created by user on 17/02/2020.
//

#ifndef MACHINELEARNING_MODEL_H
#define MACHINELEARNING_MODEL_H


class Model
{
public:
    Model(int dimInputNumber, int dimOutputNumber);

protected:
    double* input;
    double* output;
};


#endif //MACHINELEARNING_MODEL_H
