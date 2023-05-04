// This program is implemented by referring the R project at https://github.com/yain22/bayesestdft.
// The current version of this implementation is not able to give the same result as the reference project.
// This might be the problem of generating the random normal or uniform distributions. Any of modification or 
// improvement are welcome.
// 04/05/2023.
// Email: arifle@163.com

#include "bayeslnp.h"


#define PI 3.141592653589793238462643

using namespace std;

double alphaBGA(const double & eta_new, const double & eta_old, const std::vector<double>& y, const int & N, const int & a, const double & b)
{
	double e = exp(1);

	// Likelihood ratio part
	double f1 = std::lgamma((pow(e, eta_new) + 1) / 2) - (eta_new / 2 + log(PI) / 2 + std::lgamma(pow(e, eta_new) / 2));
	double f2 = std::lgamma((pow(e, eta_old) + 1) / 2) - (eta_old / 2 + log(PI) / 2 + std::lgamma(pow(e, eta_old) / 2));

	std::vector<double> midvecf3 = veclog(vecaddscalar(vecdivscalar(vecpow(y, 2), exp(eta_new)), 1));
	std::vector<double> midvecf4 = veclog(vecaddscalar(vecdivscalar(vecpow(y, 2), exp(eta_old)), 1));

	double f3 = (exp(eta_new) + 1) / 2 * std::accumulate(midvecf3.begin(), midvecf3.end(), 0);
	double f4 = (exp(eta_old) + 1) / 2 * std::accumulate(midvecf4.begin(), midvecf4.end(), 0);

	// Prior ratio part
	double p1 = a*(eta_new - eta_old);
	double p2 = b*(exp(eta_new) - exp(eta_old));

	// Result
	return (min( exp(N*(f1 - f2) - (f3 - f4) + (p1 - p2)), 1.0));
}


double BayesGA(const std::vector<double> & y, const double & ini_nu, const int & S, const double & delta)
{
	// Sample size
	int N = y.size();

	// Make a room
	std::vector<double> nu(S);
	std::vector<double> eta(S);

	// Initial value
	nu[0] = ini_nu;
	eta[0] = log(nu[0]);

	double u, eta_star, sum=nu[0];
	for (int i = 0; i < S - 1; i++)
	{
		// A. change of variable
		eta[i] = log(nu[i]);

		// B. MH algorithm
		// a. criterion function is alphaBGA()
		// b. choose a threshold:
		u = runif(1, 0, 1)[0];

		// c. Draw an initial proposal:
		//eta_star = rnorm(1, eta[i], sqrt(2 * delta))[0];
		eta_star = rnorm(1, eta[i], sqrt(2 * delta))[0];

		// d. MH core step
		if (u < alphaBGA(eta_star, eta[i], y, N))
			eta[i + 1] = eta_star;
		else
			eta[i + 1] = eta[i];

		// C. Change of variable 
		nu[i + 1] = exp(eta[i + 1]);
		sum += nu[i+1];
	} // end for

	return ( sum / nu.size());
}