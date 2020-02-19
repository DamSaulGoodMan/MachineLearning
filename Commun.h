//
// Created by user on 19/02/2020.
//

#ifndef MACHINELEARNING_COMMUN_H
#define MACHINELEARNING_COMMUN_H


#include <cstdlib>


class Commun
{
public :
    inline static double fRand(double fMin, double fMax)
    {
        double f = (double) rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }
};


#endif //MACHINELEARNING_COMMUN_H
