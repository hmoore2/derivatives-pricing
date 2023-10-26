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
    int nScenarios;
    /*  The number of steps in the calculation */
    int nSteps;
    /*  Price the option */
    double price( const ContinuousTimeOption& option,
                  const EquityModel& model );

};

void testMonteCarloPricer();