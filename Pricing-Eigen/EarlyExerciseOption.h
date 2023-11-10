#pragma once

#include "stdafx.h"

class EarlyExerciseOption {
public:
    /*  Virtual destructor */
    virtual ~EarlyExerciseOption() {};
    /*  The maturity of the option */
    virtual double GetMaturity() const = 0;
};
