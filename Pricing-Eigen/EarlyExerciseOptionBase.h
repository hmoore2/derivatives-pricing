#pragma once

#include "EarlyExerciseOption.h"

class EarlyExerciseOptionBase :
        public EarlyExerciseOption {
public:
    virtual ~EarlyExerciseOptionBase() {}

    double getMaturity() const {
        return maturity;
    }

    void setMaturity(double maturity) {
        this->maturity = maturity;
    }

    double getStrike() const {
        return strike;
    }

    void setStrike(double strike) {
        this->strike = strike;
    }
private:
    double maturity;
    double strike;

};