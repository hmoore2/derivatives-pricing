//
// Created by Henry Moore on 20/10/2023.
//

#include "BlackScholesModel.h"

using namespace std;
#include "MathsLib.h"
BlackScholesModel::BlackScholesModel() :
        drift(0.0),
        stockPrice(0.0),
        volatility(0.0),
        riskFreeRate(0.0),
        date(0.0) {
}

/**
 *  Creates a price path according to the model parameters
 */
MatrixXd BlackScholesModel::
generateRiskNeutralPricePaths(
        double toDate,
        int nPaths,
        int nSteps ) const {
    return generatePricePaths( toDate, nPaths, nSteps, riskFreeRate );
}

/**
 *  Creates a price path according to the model parameters
 */
MatrixXd BlackScholesModel::generatePricePaths(
        double toDate,
        int nPaths,
        int nSteps ) const {
    return generatePricePaths( toDate, nPaths, nSteps, drift );
}



/**
 *  Creates a price path according to the model parameters
 */
MatrixXd BlackScholesModel::generatePricePaths(
        double toDate,
        int nPaths,
        int nSteps,
        double drift ) const {
    MatrixXd path(nPaths, nSteps);

    double dt = (toDate-date)/nSteps;
    double a = (drift - volatility*volatility*0.5)*dt;
    double b = volatility*sqrt(dt);
    MatrixXd currentLogS=log(stockPrice)*MatrixXd::Ones(nPaths,1);
    for (int i=0; i<nSteps; i++) {
        MatrixXd vals = randn( nPaths,1 );
        // vals contains epsilon
        vals*=b;
        vals.array()+=a;   // vals now contains dLogS
        vals+=currentLogS; // vals now contains logS
        currentLogS = vals;
        vals = vals.array().exp(); // vals now contains S
        path.col(i) = vals;
    }
    return path;
}