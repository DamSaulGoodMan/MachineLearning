//
// Created by user on 17/02/2020.
//

#ifndef MACHINELEARNING_MODEL_H
#define MACHINELEARNING_MODEL_H


class Model
{
public:
    Model(int dimInputNumber, int dimOutputNumber);

    virtual void train(double valuesOfEntry[],
            int entryNumber,
            double predictState[],
            double trainingStep,
            int epoch) = 0;

    virtual int predict(double *entry) = 0;

    virtual ~Model();

    virtual ~Model();

protected:
    double* input;
    double* output;
};


#endif //MACHINELEARNING_MODEL_H
