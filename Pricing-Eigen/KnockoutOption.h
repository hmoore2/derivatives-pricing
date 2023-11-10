#pragma once

#include "ContinuousTimeOptionBase.h"

/**
 *   An option with a barrier
 */
class KnockoutOption : public ContinuousTimeOptionBase {
public:
    virtual ~KnockoutOption() {}

    double GetBarrier() const {
        return barrier_;
    }

    void SetBarrier(double barrier) {
        this->barrier_=barrier;
    }

    bool IsPathDependent() const {
        return true;
    }
private:
    double barrier_;
};