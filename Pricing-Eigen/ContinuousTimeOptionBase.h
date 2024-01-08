#pragma once

#include "ContinuousTimeOption.h"
#include "BlackScholesModel.h"

/**
 *  Convenience class for eliminating the drudgery of
 *  writing option classes
 */
class ContinuousTimeOptionBase : public ContinuousTimeOption {
public:
    virtual ~ContinuousTimeOptionBase() {}

    double GetMaturity() const {
        return maturity_;
    }

    void SetMaturity(double maturity ) {
        this->maturity_ = maturity;
    }

    double GetStrike() const {
        return strike_;
    }

    /*
     *  Convenience method to calculate an approximate Price
     *  for the option using the most appropriate method for
     *  the given option. Note that since you can't control
     *  the accuracy of the calculation this isn't a good method
     *  for general use, but is handy for tests.
     */
    virtual double Price(const BlackScholesModel& model ) const;

    void SetStrike(double strike ) {
        this->strike_ = strike;
    }

private:
    double maturity_;
    double strike_;
};

////////////////


void TestContinuousTimeOptionBase();
