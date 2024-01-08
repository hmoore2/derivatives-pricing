//
// Created by Henry Moore on 20/10/2023.
//

#pragma once

#include "stdafx.h"
#include "Eigen/Dense"
#include "MathsLib.h"
using Eigen::MatrixXd;
using Eigen::VectorXd;

class BlackScholesModel {
public:
    BlackScholesModel();

    double drift_;
    double stock_price_;
    double volatility_;
    double risk_free_rate_;
    double date_;

    MatrixXd GeneratePricePaths(
            double to_date,
            int n_paths,
            int n_steps, std::shared_ptr<RandomNumberGenerator> random) const;

    MatrixXd GenerateRiskNeutralPricePaths(
            double to_date,
            int n_paths,
            int n_steps, std::shared_ptr<RandomNumberGenerator> random) const;


  double GetRiskFreeRate() const {
        return risk_free_rate_;
    }
    double GetDate() const {
        return date_;
    }

private:

    MatrixXd GeneratePricePaths(
            double to_date,
            int n_paths,
            int n_steps,
            double drift, const std::shared_ptr<RandomNumberGenerator>& random) const;

};

//void testBlackScholesModel();