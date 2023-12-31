//
// Created by Henry Moore on 21/10/2023.
//
#include "gtest/gtest.h"
#include "../Pricing-Eigen/MathsLib.h"

TEST(MathsLib, Bisection){
    auto lambda = [](double x){
        return pow(x,2) - 2;
    };
    double actual = Bisection(lambda, 0, 2, 0.01, 0);
    double expected = sqrt(2);
    ASSERT_NEAR( actual, expected, 0.01);

    auto lambda2 = [](double x){
        return sin(x) - 0.5;
    };
    double actual2 = Bisection(lambda2, 0, 2, 0.0000001, 0);
    double expected2 = kPi/6;
    ASSERT_NEAR( actual2, expected2, 0.000001);
}



TEST(MathsLib, lambdaIntegral){
    auto lambda = [](double x) {
        return sqrt(1 + pow(sin(x), 2));
    };

    double actual = Integrate(lambda, 0, kPi, 1000);
    double expected = 3.820197789;
    ASSERT_NEAR(actual, expected, 0.000001);
}


