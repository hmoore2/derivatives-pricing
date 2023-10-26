#include "AmericanCallOption.h"
#include "MathsLib.h"
#include <cmath>
#include <numeric>

using namespace std;

double AmericanCallOption::price(const BlackScholesModel& bsm, int nAssetSteps) const {
    // Generate grid
    double dS = 2 * getStrike() / nAssetSteps; // Infinity is twice the strike
    double dt = 0.9 / pow(bsm.volatility, 2) / pow(nAssetSteps, 2); // For stability
    int nTimeSteps = static_cast<int>(getMaturity() / dt) + 1; // Number of time steps
    double sharePrice = bsm.stockPrice; // Current share price
    dt = getMaturity() / nTimeSteps; // Time step size

    MatrixXd V(nAssetSteps + 1, nTimeSteps + 1); // Option value array
    VectorXd S(nAssetSteps + 1); // Asset array
    VectorXd payoff(nAssetSteps+1); // Payoff array

    for (int i = 0; i <= nAssetSteps; i++) {
        S(i) = i * dS; // Set up S array
        V(i, 0) = fmax(S(i) - getStrike(), 0);  // Boundary condition at expiry
        payoff(i) = V(i, 0); // For cutoff method later
    }

    for (int k = 1; k <= nTimeSteps; k++) { // Time loop
        for (int i = 1; i <= nAssetSteps - 1; i++) { // Asset loop. End points treated separately
            double Delta = (V(i + 1, k - 1) - V(i - 1, k - 1)) / 2 / dS; // Central difference
            double Gamma = (V(i + 1, k - 1) - 2 * V(i, k - 1) + V(i - 1, k - 1)) / pow(dS, 2);
            double Theta = -0.5 * pow(bsm.volatility, 2) * pow(S(i), 2) * Gamma - bsm.riskFreeRate * S(i) * Delta + bsm.riskFreeRate * V(i, k - 1);
            V(i, k) = V(i, k - 1) - dt * Theta;
        }
        V(0, k) = V(0, k - 1) * (1 - bsm.riskFreeRate * dt); // Boundary condition at S = 0
        V(nAssetSteps, k) = 2 * V(nAssetSteps - 1, k) - V(nAssetSteps - 2, k); // Boundary condition at S=infinity

        // Cutoff method (value of option cannot be less than payoff - no arbitrage condition)
        for (int i = 0; i <= nAssetSteps; i++) {
            V(i, k) = fmax(V(i, k), payoff(i));
       }

    }
    // Linear interpolation for price given asset
    double lowVal = V(int(round(sharePrice/dS)),nTimeSteps);
    double highVal = V(int(round(sharePrice/dS)+1), nTimeSteps);
    double interpFactor = (sharePrice / dS) - round(sharePrice / dS);
    double interPolatedPrice = lerp(lowVal,highVal,interpFactor);

    return interPolatedPrice;

}
