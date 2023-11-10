#include "AmericanCallOption.h"
#include "MathsLib.h"
#include <cmath>
#include <numeric>

using namespace std;

double AmericanCallOption::Price(const BlackScholesModel& bsm, int n_asset_steps) const {
    // Generate grid
    double ds = 2 * GetStrike() / n_asset_steps; // Infinity is twice the strike
    double dt = 0.9 / pow(bsm.volatility_, 2) / pow(n_asset_steps, 2); // For stability
    int n_time_steps = static_cast<int>(GetMaturity() / dt) + 1; // Number of time steps
    double share_price = bsm.stock_price_; // Current share Price
    dt = GetMaturity() / n_time_steps; // Time step size

    MatrixXd v(n_asset_steps + 1, n_time_steps + 1); // Option value array
    VectorXd s(n_asset_steps + 1); // Asset array
    VectorXd payoff(n_asset_steps+1); // Payoff array

    for (int i = 0; i <= n_asset_steps; i++) {
	  s(i) = i * ds; // Set up s array
        v(i, 0) = fmax(s(i) - GetStrike(), 0);  // Boundary condition at expiry
        payoff(i) = v(i, 0); // For cutoff method later
    }

    for (int k = 1; k <= n_time_steps; k++) { // Time loop
        for (int i = 1; i <= n_asset_steps - 1; i++) { // Asset loop. End points treated separately
            double delta = (v(i + 1, k - 1) - v(i - 1, k - 1)) / 2 / ds; // Central difference
            double gamma = (v(i + 1, k - 1) - 2 * v(i, k - 1) + v(i - 1, k - 1)) / pow(ds, 2);
            double theta = -0.5 * pow(bsm.volatility_, 2) * pow(s(i), 2) * gamma - bsm.risk_free_rate_ * s(i) * delta + bsm.risk_free_rate_ * v(i, k - 1);
		  v(i, k) = v(i, k - 1) - dt * theta;
        }
	  v(0, k) = v(0, k - 1) * (1 - bsm.risk_free_rate_ * dt); // Boundary condition at s = 0
        v(n_asset_steps, k) = 2 * v(n_asset_steps - 1, k) - v(n_asset_steps - 2, k); // Boundary condition at s=infinity

        // Cutoff method (value of option cannot be less than Payoff - no arbitrage condition)

        for (int i = 0; i <= n_asset_steps; i++) {
		  v(i, k) = fmax(v(i, k), payoff(i));
       }

    }
    // Linear interpolation for Price given asset
    double low_val = v(int(round(share_price/ds)), n_time_steps);
    double high_val = v(int(round(share_price/ds)+1), n_time_steps);
    double interp_factor = (share_price / ds) - round(share_price / ds);
    double interpolated_price = lerp(low_val, high_val, interp_factor);

    return interpolated_price;
}
