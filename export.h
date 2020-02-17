//
// Created by user on 17/02/2020.
//

#ifndef MACHINELEARNING_EXPORT_H
#define MACHINELEARNING_EXPORT_H

#ifdef _WIN32
# define EXPORTED  __declspec( dllexport )
#else
# define EXPORTED
#endif

#endif //MACHINELEARNING_EXPORT_H
