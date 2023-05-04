// This program is implemented by referring the R project at https://github.com/yain22/bayesestdft.
// The current version of this implementation is not able to give the same result as the reference project.
// This might be the problem of generating the random normal or uniform distributions. Any of modification or 
// improvement are welcome.
// 04/05/2023.
// Email: arifle@163.com

#include "bayeslnp.h"

using namespace std;


// pow() of a vector.
template<typename T1, typename T2>
std::vector<T1> vecpow(const std::vector<T1> & vecd, const T2 & exponential)
{
	std::vector<T1> res;
	for (int i = 0; i < vecd.size(); i++)
		res.push_back(std::pow(vecd[i], exponential));

	return res;
}

// vector plus a scalar
template<typename T1, typename T3>
std::vector<T1> vecaddscalar(const std::vector<T1> & vecT, T3 scalarT2)
{
	std::vector<T1> res;
	for (auto& x : vecT) {
		res.push_back(x + scalarT2);
	}
	return res;
}

// log of a vector
template<typename T>
std::vector<T> veclog(const std::vector<T> & vecT)
{
	std::vector<T> res;
	for (auto& x : vecT) {
		res.push_back(std::log(x));
	}
	return res;
}

// vector divide by a scalar.
template<typename T1, typename T2>
std::vector<T1> vecdivscalar(const std::vector<T1> & vecT, T2 scalarT2)
{
	std::vector<T1> res;
	for (auto& x : vecT) {
		res.push_back(x / scalarT2);
	}
	return res;
}

// the alpha() in BayesLNP.
double alphaBLNP(const double & eta_new, const double & eta_old, const std::vector<double>& y, const int & N)
{
	double e = exp(1);
	double f1 = lgamma((pow(e, eta_new) + 1) / 2) - (eta_new / 2 + log(M_PI) / 2 + lgamma(pow(e, eta_new) / 2));
	double f2 = lgamma((pow(e, eta_old) + 1) / 2) - (eta_old / 2 + log(M_PI) / 2 + lgamma(pow(e, eta_old) / 2));
	std::vector<double> midVecf3 = veclog( vecaddscalar( vecdivscalar( vecpow(y, 2), std::exp(eta_new) ), 1 ) );
	std::vector<double> midVecf4 = veclog( vecaddscalar( vecdivscalar( vecpow(y, 2), std::exp(eta_old) ), 1 ) );
	double f3 = ((exp(eta_new) + 1) / 2) * std::accumulate(midVecf3.begin(), midVecf3.end(), 0);
	double f4 = ((exp(eta_old) + 1) / 2) * std::accumulate(midVecf4.begin(), midVecf4.end(), 0);

	return (min(exp(N*(f1 - f2) - (f3 - f4)), 1.0));
}

// bayesLNP() with default parameters where
// ini_nu = 1.0, S = 1000, mu = 1.0 and sigma_std = 1.0;
double BayesLNP(const std::vector<double> & y, const double & ini_nu, const int & S, const double & mu, const double & sigma_sq)
{
	// Sample size
	int N = y.size();

	// Create two vectors in length of S.
	std::vector<double> nu(S); 
	std::vector<double> eta(S);

	// Initial value
	nu[0] = ini_nu;
	eta[0] = std::log(nu[0]); // Return the same as log(nu[0])

	double eta_new, eta_old;
	double eta_star, sum = nu[0]; 
	for (int i = 0; i < (S - 1); i++)
	{
		// A. change of variable
		eta[i] = log(nu[i]);

		// B. ESS
		// a. Choose an ellipse centered at mu:
		std::vector<double> rho = rnorm(1, mu, sqrt(sigma_sq));

		// b. The criterion function is alphaLNP()

		// c. Choose a threshold and fix:
		std::vector<double> u = runif(1, 0, 1);

		// d. Draw an initial proposal:
		std::vector<double> phi = runif(1, -M_PI, M_PI);
		// Note that the rnorm() with n=1 returns only a single element vector, so that we use phi[0] and rho[0] here.
		eta_star = (eta[i] - mu)*cos(phi[0]) + (rho[0] - mu)*sin(phi[0]) + mu; 

		// e. #SS core step
		eta_new = eta_star, eta_old = eta[i];
		if (u[0] < alphaBLNP(eta_new, eta_old, y, N))
		{
			eta[i + 1] = eta_star;
		}
		else
		{
			// Define a bracket:
			double phi_min = -M_PI, phi_max = M_PI;
			//eta_new = eta_star, eta_old = eta[i];
			while (u[0] >= alphaBLNP(eta_new, eta_old, y, N))
			{
				// Shrink the bracket and try a new point:
				if (phi[0] > 0)
					phi_max = phi[0];
				else
					phi_min = phi[0];

				phi = runif(1, -M_PI, M_PI);
				eta_star = (eta[i] - mu)*cos(phi[0]) + (rho[0] - mu)*sin(phi[0]) + mu;
				eta_new = eta_star, eta_old = eta[i];
			} // end while
			eta[i + 1] = eta_star;
		} // end if-else

		// C. change of variable
		nu[i + 1] = exp(eta[i + 1]);
		sum += nu[i + 1];
	} // end for
	
	return (sum/nu.size());
}

