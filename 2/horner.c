#include <stdio.h>
#include <math.h>

int main(void)
{
	int m, n;
	double x, S;

	n = 10;
	x = 1.0;

	S=1.0;
	for (m = n; m > 0; m--) {
		S = 1.0 + x * S/(double)m;
	}

	printf("|S-exp(x)|=%g for n = %d and x = %g \n", fabs(S - exp(1.0)), n , x);
	
	return 0;
}
