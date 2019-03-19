#ifndef SIMU_H
#define SIMU_H
#include <math.h>
#include "Matrix.h"
float normal();
Matrix iidGaussian(int dim);
Matrix GaussianVector(Matrix* M, Matrix* mean);
Matrix mixing(Matrix M, Matrix N, int scoreM, int scoreN);
#endif
