// A weak demo.
// This program is implemented by referring the R project at https://github.com/yain22/bayesestdft.
// The current version of this implementation is not able to give the same result as the reference project.
// This might be the problem of generating the random normal or uniform distributions. Any of modification or 
// improvement are welcome.
// 04/05/2023.
// Email: arifle@163.com

// The bayeslnp.R gives results around 0.5 (maybe 0.05) which I don't remember well, and the bayesga.R returns 
// a little bit larger result.


#include "bayeslnp.h"

#include <chrono>
#include <fstream>

int main()
{
	std::vector<double> sample = rnorm(5, 0, 1);

	std::cout << "Random sampled values from standard normal distribution: " << std::endl;
	for (double x : sample) {
		std::cout << "  " << x << std::endl;
	}

	std::cout << "----------------" << std::endl;

	std::vector<double> y1 = rnorm(100, 0, 1);
	double eta_old = 1, eta_new = 0;
	int N = 100;
	std::cout << alphaBLNP(eta_new, eta_old, y1, 100) << "alpha" << std::endl;


	std::ifstream fin;
	std::vector<double> y2;
	double tmpd;
	fin.open("f:/yourpath/data_x.txt", std::ios::in);
	while (!fin.eof()){
		fin >> tmpd;
		y2.push_back(tmpd);
	}
	fin.close();
	y2.pop_back();
	std::cout << "size of data: " << y2.size() << "|" << y2[y2.size()-1] << std::endl;

	std::chrono::time_point<std::chrono::system_clock> t0 = std::chrono::system_clock::now();

	std::cout << "LNP " << BayesGA(y1) << std::endl;

	std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
	std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>( t1 - t0);
	std::cout << "time: "<< diff.count() << std::endl;
	
	std::vector<int> a(2);
	std::cout << a[3] << std::endl;

	return 0;
}