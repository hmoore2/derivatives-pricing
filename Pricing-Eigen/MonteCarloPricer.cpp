//
// Created by Henry Moore on 21/10/2023.
//

#include "MonteCarloPricer.h"

#include "MathsLib.h"
#include "CallOption.h"

using namespace std;


MonteCarloPricer::MonteCarloPricer() :
        nScenarios(10000),
        nSteps(10) {
}

double MonteCarloPricer::price(
        const ContinuousTimeOption& option,
        const EquityModel& model ) {
    int nSteps = this->nSteps;
    if (!option.isPathDependent()) {
        nSteps = 1;
    }
    double total = 0.0;

    // We price at most one million scenarios at a time to avoid running out of memory
    int batchSize = 10000000/nSteps;
    if (batchSize<=0) {
        batchSize = 1;
    }

    int scenariosRemaining = nScenarios;
    while (scenariosRemaining>0) {

        int thisBatch = batchSize;
        if (scenariosRemaining<batchSize) {
            thisBatch = scenariosRemaining;
        }

        MatrixXd paths= model.
                generateRiskNeutralPricePaths(
                option.getMaturity(),
                thisBatch,
                nSteps );
        MatrixXd payoffs = option.payoff( paths );
        total+= payoffs.rowwise().sum().sum();
        scenariosRemaining-=thisBatch;
    }
    double mean = total/nScenarios;
    double r = model.getRiskFreeRate();
    double T = option.getMaturity() - model.getDate();
    return exp(-r*T)*mean;
}