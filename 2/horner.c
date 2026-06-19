#include <stdio.h>
#include <math.h>

double horner(double x, double s, int n)
{
    int m;

    s=1.0;
	for (m = n; m > 0; m--) {
		s = 1.0 + x * s/(double)m;
	}

    return s;
}

int main(void)
{
	int n = 50;
	double x = 1.0;
    double s = 0;
    double answer = 0;

	for (int i = 1; i < n ; i++) {
        answer = horner(x, s, i);
        printf("|S-exp(x)|=%g for n = %d and x = %g \n", fabs(answer - exp(1.0)), i , x);
	}

	return 0;
}
