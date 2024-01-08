//
// Created by Henry Moore on 20/10/2023.
//

#include "BlackScholesModel.h"
using namespace std;
#include "MathsLib.h"
BlackScholesModel::BlackScholesModel() :
	drift_(0.0),
	stock_price_(0.0),
	volatility_(0.0),
	risk_free_rate_(0.0),
	date_(0.0) {
}

/**
 *  Creates a Price path according to the model parameters
 */
MatrixXd BlackScholesModel::
GenerateRiskNeutralPricePaths(
        double to_date,
        int n_paths,
        int n_steps, std::shared_ptr<RandomNumberGenerator> random ) const {
    return GeneratePricePaths(to_date, n_paths, n_steps, risk_free_rate_, random );
}

/**
 *  Creates a Price path according to the model parameters
 */
MatrixXd BlackScholesModel::GeneratePricePaths(
        double to_date,
        int n_paths,
        int n_steps, std::shared_ptr<RandomNumberGenerator> random ) const {
    return GeneratePricePaths(to_date, n_paths, n_steps, drift_, random);
}

/**
 *  Creates a Price path according to the model parameters
 */
MatrixXd BlackScholesModel::GeneratePricePaths(
        double to_date,
        int n_paths,
        int n_steps,
        double drift, const std::shared_ptr<RandomNumberGenerator>& random) const {
    MatrixXd path(n_paths, n_steps);
	double dt = (to_date-date_)/n_steps;
    double a = (drift - volatility_*volatility_*0.5)*dt;
    double b = volatility_*sqrt(dt);
    MatrixXd current_log_s=log(stock_price_)*MatrixXd::Ones(n_paths, 1);
    for (int i=0; i<n_steps; i++) {
	  MatrixXd vals = random->GetGaussians(n_paths, 1);
	  // vals contains epsilon
	  vals*=b;
	  vals.array()+=a;   // vals now contains dLogS
	  vals+=current_log_s; // vals now contains logS
	  current_log_s = vals;
	  vals = vals.array().exp(); // vals now contains S
	  path.col(i) = vals;
    }
    return path;
}


