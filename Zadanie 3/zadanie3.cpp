#include <iostream>
#include <cstring>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double feval(char* function,double argument){
    if (strcmp(function,"sin")==0)  return sin(argument);
    if (strcmp(function,"cos")==0)  return cos(argument);
    if (strcmp(function,"tan")==0)  return tan(argument);
    if (strcmp(function,"exp")==0)  return exp(argument);
    if (strcmp(function,"log")==0)  return log(argument);
    if (strcmp(function,"sqrt")==0)  return sqrt(argument);
    return -1;
}

int main(int argc, char **argv) {

    char* funct = argv[1];
    int degree = std::atoi(argv[2]);
    double interval_start = std::atof(argv[3]);
    double interval_stop = std::atof(argv[4]);
    double d = M_PI / (2 * degree + 2);
    double X[1024];

    for (unsigned int i = 0; i < degree + 1; i++) {
        X[i] = 0;
    }

    for (int i = 1; i <= degree + 1; ++i) {
        X[i - 1] = cos((2 * i - 1) * d);
    }

    for (int i = 0; i <= degree; ++i) {
        X[i] = (interval_stop - interval_start) * X[i] / 2 + (interval_start + interval_stop) / 2;
    }

    printf("X: ");
    for (unsigned int i = 0; i < degree + 1; i++) {
        printf("%f   ", X[i]);
    }
    printf("\n");

    for (unsigned int i = 0; i < degree + 1; i++) {
        X[i] = feval(funct, X[i]);
    }

    printf("Y: ");
    for (unsigned int i = 0; i < degree + 1; i++) {
        printf("%f   ", X[i]);
    }
    printf("\n");

    return 0;
}
