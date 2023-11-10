#pragma once

#include "EarlyExerciseOption.h"

class EarlyExerciseOptionBase :
        public EarlyExerciseOption {
public:
    virtual ~EarlyExerciseOptionBase() {}

    double GetMaturity() const {
        return maturity_;
    }

    void SetMaturity(double maturity) {
        this->maturity_ = maturity;
    }

    double GetStrike() const {
        return strike_;
    }

    void SetStrike(double strike) {
        this->strike_ = strike;
    }
private:
    double maturity_;
    double strike_;

};