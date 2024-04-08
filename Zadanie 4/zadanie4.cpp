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

void richardson(char* f, double const a, double const h, unsigned const int M) {
	std::vector<std::vector<double> > D (M+1, std::vector<double> (M+1, 0));

	for (int n = 0; n <= M; n++) {
		double dh = 0;
		dh = h / std::pow(2, n);
		D[n][0] = (feval(f,a+dh)-feval(f,a-dh))/(2*dh);
	}

	for (int k = 1; k <= M; k++) {
		for (int n = k; n <= M; n++) {
			D[n][k]=D[n][k-1]+(D[n][k-1]-D[n-1][k-1])/std::pow(4, k-1);
		}
	}

	for (unsigned int i = 0; i <= M; i++) {
		for (unsigned int j = 0; j <= M; j++) {
			std::cout << std::setw(10);
			std::cout << std::fixed;
			std::cout << std::setprecision(4);
			std::cout << D[i][j];
		}
		printf("\n");
	}
}

int main(int argc, char **argv) {
	richardson(argv[1], atof(argv[2]), atof(argv[3]), atoi(argv[4]));
}
