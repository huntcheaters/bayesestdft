// R source code.
// 04/05/2023.
// Email: arifle@163.com

#include "rmath.h"
#include <time.h>

// arithmetic.c 
double R_NaN = NAN;
double R_PosInf = INFINITY;
double R_NegInf = -INFINITY;


// fmax2.c
double fmax2(double x, double y)
{
#ifdef IEEE_754
	if (ISNAN(x) || ISNAN(y))
		return x + y;
#endif
	return (x < y) ? y : x;
}


// fmin2.c
double fmin2(double x, double y)
{
#ifdef IEEE_754
	if (ISNAN(x) || ISNAN(y))
		return x + y;
#endif
	return (x < y) ? x : y;
}


// runif.c
double runif(double a, double b)
{
	if (!R_FINITE(a) || !R_FINITE(b) || b < a)	ML_WARN_return_NAN;

	if (a == b)
		return a;
	else {
		double u;
		/* This is true of all builtin generators, but protect against
		user-supplied ones */
		do { u = unif_rand(); } while (u <= 0 || u >= 1);
		return a + (b - a) * u;
	}
}

std::vector<double> runif(const int & n, const double & a, const double & b)
{
	std::vector<double> ret;
	for (int i = 0; i < n; i++)
		ret.push_back(runif(a, b));

	return ret;
}


// rnorm.c
double rnorm(double mu, double sigma)
{
	if (ISNAN(mu) || !R_FINITE(sigma) || sigma < 0.)
		ML_WARN_return_NAN;
	if (sigma == 0. || !R_FINITE(mu))
		return mu; /* includes mu = +/- Inf with finite sigma */
	else
		return mu + sigma * norm_rand();
}

std::vector<double> rnorm(const int & n, const double & mu, const double & sigma)
{
	std::vector<double> ret;
	for (int i = 0; i < n; i++)
		ret.push_back(rnorm(mu, sigma));

	return ret;
}

static unsigned int I1 = 1234 + (unsigned int)(time(NULL)), I2 = 5678+(unsigned int)(time(NULL));
// standalone/sunif.c
double unif_rand(void)
{
	I1 = 36969 * (I1 & 0177777) + (I1 >> 16) ;
	I2 = 18000 * (I2 & 0177777) + (I2 >> 16) ;
	return ((I1 << 16) ^ (I2 & 0177777)) * 2.328306437080797e-10; /* in [0,1) */
}


// Arithmatic.c
/* Mainly for use in packages */
int R_finite(double x)
{
#ifdef HAVE_WORKING_ISFINITE
	return isfinite(x);
#else
	return (!isnan(x) & (x != R_PosInf) & (x != R_NegInf));
#endif
}