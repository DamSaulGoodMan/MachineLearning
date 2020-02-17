#include "api.h"

#include <iostream>


extern "C"
{

    EXPORTED unsigned int return42()
    {
        return 42;
    }

}

