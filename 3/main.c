#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x) {
    return 1.0 / (1.0 + x);
}

double SimpInt(int n, double a, double b) {
    int i;
    double S, h;

    S = 0.0;
    h = (b - a)/(double)n;
    
    for (i = 0; i < n; i++) {
        S += func(i * h + a) + 4.0 * func((i + 0.5)* h + a) + func((i + 1.0)* h + a);
    }
    S *= h/6.0;

    return S;
}

int main(void) {
    int n;
    double a, b, S, S0, err;

    S0 = log(3.0);
    a = 0.0;
    b = 2.0;

    for (n = 10; n <= 1e+7; n *= 10) {
        S = SimpInt(n, a, b);
        err = fabs((S - S0)/ S0);
        printf("n%8d Simpson=%g error=%g\n", n, S, err);
    }
}