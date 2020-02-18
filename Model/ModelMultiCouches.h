//
// Created by user on 18/02/2020.
//

#ifndef MACHINELEARNING_MODELMULTICOUCHES_H
#define MACHINELEARNING_MODELMULTICOUCHES_H


#include "Model.h"


class ModelMultiCouches : public Model
{
public:
    explicit ModelMultiCouches(int entryNumber);

    void initEntry(double *entryValue) override;

private:
    double** neurones;
    double*** weight;
};


#endif //MACHINELEARNING_MODELMULTICOUCHES_H
