// R source code.
// 04/05/2023.
// Email: arifle@163.com

#ifndef RMATH_H
#define RMATH_H

#define M_PI 3.141592653589793238462643


#include "rnmath.h"

// config.h.in
/* Define if isfinite() is correct for -Inf/NaN/Inf. */
#undef HAVE_WORKING_ISFINITE 

double norm_rand(void);

double fmax2(double x, double y);

double fmin2(double x, double y);

double runif(double a, double b);
std::vector<double> runif(const int & n, const double & a, const double & b);

double rnorm(double mu, double sigma);
std::vector<double> rnorm(const int & n, const double & mu, const double & sigma);

double qnorm5(double p, double mu, double sigma, int lower_tail, int log_p);

double unif_rand(void); // Random.h


#endif