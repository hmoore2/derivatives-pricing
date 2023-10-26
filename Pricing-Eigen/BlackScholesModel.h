//
// Created by Henry Moore on 20/10/2023.
//

#pragma once

#include "stdafx.h"
#include "Eigen/Dense"
#include "EquityModel.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

class BlackScholesModel : public EquityModel {
public:
    BlackScholesModel();
    double drift;
    double stockPrice;
    double volatility;
    double riskFreeRate;
    double date;

    MatrixXd generatePricePaths(
            double toDate,
            int nPaths,
            int nSteps) const;

    MatrixXd generateRiskNeutralPricePaths(
            double toDate,
            int nPaths,
            int nSteps) const;

    double getRiskFreeRate() const {
        return riskFreeRate;
    }
    double getDate() const {
        return date;
    }

private:

    MatrixXd generatePricePaths(
            double toDate,
            int nPaths,
            int nSteps,
            double drift) const;
};

//void testBlackScholesModel();