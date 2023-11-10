//
// Created by Henry Moore on 21/10/2023.
//

#pragma once

#include "stdafx.h"
#include "ContinuousTimeOption.h"
#include "BlackScholesModel.h"

class MonteCarloPricer {
public:
    /*  Constructor */
    MonteCarloPricer();
    /*  Number of scenarios */
    int n_scenarios_;
    /*  The number of steps in the calculation */
    int n_steps_;
    /*  Price the option */
    double Price(const ContinuousTimeOption& option,
				 const BlackScholesModel& model, const bool antithetic);

};

