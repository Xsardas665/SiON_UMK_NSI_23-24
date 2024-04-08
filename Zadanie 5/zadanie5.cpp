#include <iostream>
#include <iomanip>
#include <cstring>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define pr(x) std::cout << x << std::endl

double feval(char* fn, double arg){
	if (strcmp(fn,"sin")==0)  return sin(arg);
	if (strcmp(fn,"cos")==0)  return cos(arg);
	if (strcmp(fn,"tan")==0)  return tan(arg);
	if (strcmp(fn,"exp")==0)  return exp(arg);
	if (strcmp(fn,"log")==0)  return log(arg);
	if (strcmp(fn,"sqrt")==0) return sqrt(arg);
	return -1;
}

std::vector< std::vector<double> > romberg(char* f, double const a, double const b, unsigned const int M) {
	std::vector< std::vector<double> > R (M+1, std::vector<double> (M+1, 0));

	double h = b - a;
	R[0][0] = h*(feval(f,a) + feval(f,b))/2;

	for (int n = 1; n <= M; n++) {
		h = h/2;

		double acc = 0;
		for (unsigned int i = 1; i <= std::pow(2, n-1); i++) {
			double tmp = (double)i;
			tmp = (2*tmp)-1;
			tmp *= h;
			tmp += a;
			tmp = feval(f, tmp);

			acc += tmp;
		}

		R[n][0] = R[n - 1][0]/2 + h * acc;

		for (unsigned int m = 1; m <= n; m++) {
			R[n][m] = R[n][m - 1] + (R[n][m - 1] - R[n - 1][m - 1]) / (std::pow(4, m) - 1);
		}
	}

	return R;
}

int main(int argc, char **argv) {
	int M = atoi(argv[4]);
	std::vector< std::vector<double> > MATR = romberg(argv[1], atof(argv[2]), atof(argv[3]), M);

	for (unsigned int i = 0; i <= M; i++) {
		for (unsigned int j = 0; j <= M; j++) {
			std::cout << std::setw(10);
			std::cout << std::fixed;
			std::cout << std::setprecision(5);
			std::cout << MATR[i][j];
		}
		printf("\n");
	}
}
