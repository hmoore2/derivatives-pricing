//
// Created by Henry Moore on 21/10/2023.
//

#include "MonteCarloPricer.h"

#include "MathsLib.h"
#include "CallOption.h"

using namespace std;


MonteCarloPricer::MonteCarloPricer() :
	n_scenarios_(10000),
	n_steps_(10) {
}

double MonteCarloPricer::Price(
        const ContinuousTimeOption& option,
        const BlackScholesModel& model, std::shared_ptr<RandomNumberGenerator> random) {
    int n_steps = this->n_steps_;
    if (!option.IsPathDependent()) {
	  n_steps = 1;
    }
    double total = 0.0;
	MatrixXd paths;
	// We Price at most one million scenarios at a time to avoid running out of memory
    int batch_size = 10000000/n_steps;
    if (batch_size<=0) {
	  batch_size = 1;
    }

    int scenarios_remaining = n_scenarios_;
    while (scenarios_remaining>0) {

        int this_batch = batch_size;
        if (scenarios_remaining<batch_size) {
		  this_batch = scenarios_remaining;
        }

		paths = model.GenerateRiskNeutralPricePaths(
				option.GetMaturity(),
				this_batch,
				n_steps, random);

        MatrixXd payoffs = option.Payoff(paths);
        total+= payoffs.rowwise().sum().sum();
	  	scenarios_remaining-=this_batch;
    }
    double mean = total/n_scenarios_;
    double r = model.GetRiskFreeRate();
    double t = option.GetMaturity() - model.GetDate();
    return exp(-r*t)*mean;
}