// Header of the bayeslnp.cpp.
// 04/05/2023.
// Email: arifle@163.com

#ifndef BAYESLNP_H
#define BAYESLNP_H


#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <numeric> // accumulate
#include <algorithm> // min
#include <ctime> // time

#include "rmath.h"



// ---------------------


// pow() of a vector.
template<typename T1, typename T2>
std::vector<T1> vecpow(const std::vector<T1> & vecd, const T2 & exponential);

// vector plus a scalar
template<typename T1, typename T3>
std::vector<T1> vecaddscalar(const std::vector<T1> & vecT, T3 scalarT2);

// log of a vector
template<typename T>
std::vector<T> veclog(const std::vector<T> & vecT);

// vector divide by a scalar.
template<typename T1, typename T2>
std::vector<T1> vecdivscalar(const std::vector<T1> & vecT, T2 scalarT2);

// the alpha() in BayesLNP.
double alphaBLNP(const double & eta_new, const double & eta_old, const std::vector<double>& y, const int & N);

// bayesLNP()
double BayesLNP(const std::vector<double> & y, const double & ini_nu = 1.0, const int & S = 1000, const double & mu = 1.0, const double & sigma_sq = 1.0);

// the alpha() in BayesGA.
double alphaBGA(const double & eta_new, const double & eta_old, const std::vector<double>& y, const int & N, const int & a = 1, const double & b = 0.1);

// BayesGA()
double BayesGA(const std::vector<double> & y, const double & ini_nu = 1.0, const int & S = 1000, const double & delta = 0.001);

#endif