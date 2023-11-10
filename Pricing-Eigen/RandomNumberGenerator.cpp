//
// Created by hezza on 10/28/2023.
//

#include "RandomNumberGenerator.h"
#include "MathsLib.h"

RandDouble rd{0,1};

MatrixXd MersenneTwister::RandUniform(int rows, int cols ) {
  MatrixXd ret(rows, cols);
  for (int i=0; i<rows; i++) {
	for (int j=0; j<cols; j++) {
	  ret(i, j) = rd();
	}
  }
  return ret;
}

MatrixXd MersenneTwister::RandNormal(int rows, int cols ) {
  MatrixXd ret = RandUniform(rows, cols);
  for (int j=0; j<cols; j++) {
	for (int i=0; i<rows; i++) {
	  ret(i,j)= Norminv(ret(i, j));
	}
  }
  return ret;
}

MatrixXd MersenneTwisterAntithetic::RandNormal(int rows, int cols)  {
	MatrixXd ret(rows, cols);
	if(cols >= rows ){ // Antithetic sampling column wise
		for (int i=0; i<rows; i++) {
			for (int j=0; j<cols/2; j++) {
				double u = rd();
				double inverse = Norminv(u);
				ret(i, j) = inverse;
				ret(i, cols/2+j) = -inverse; // Since N^{-1}(1-x) = -N^{-1}(x).
			}
		}
	}
	else{ // Antithetic sampling row wise
		for (int i=0; i<rows/2; i++) {
			for (int j=0; j<cols; j++) {
				double u = rd();
				double inverse = Norminv(u);
				ret(i, j) = inverse;
				ret(rows/2 + i, j) = -inverse;
			}
		}
	}
	return ret;
}

MatrixXd MersenneTwisterAntithetic::RandUniform(int rows, int cols)  {
	MatrixXd ret(rows, cols);
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			ret(i, j) = rd();
		}
	}
	return ret;
}



//RandomNumberGenerator::~RandomNumberGenerator() = default;
