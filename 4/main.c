#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ERR 1e-12

double func(double x, double v)
{
    double t;

    t = tanh(x/sqrt(v) + 1.0/v);
    return t*t*exp(-x*x/2.0)/sqrt(2.0*M_PI);
}

double func2(double x){
    return 2*exp(-x*x/2.0)/sqrt(2.0*M_PI);
}


double SimpInt(int n, double a, double b, double v)
{
	int i;
	double S, h;

	S =0.0;
	h = (b - a)/(double)n;
	for (i = 0; i < n; i++){
		S += func(i * h + a, v)+4.0*func((i + 0.5)* h + a, v)+func((i + 1.0)* h + a, v);
	}
	S *= h/6.0;

	return S;

}

double SimpInt2(int n, double a, double b)
{
	int i;
	double S, h;

	S =0.0;
	h = (b - a)/(double)n;
	for (i = 0; i < n; i++){
		S += func2(i * h + a)+4.0*func2((i + 0.5)* h + a)+func2((i + 1.0)* h + a);
	}
	S *= h/6.0;

	return S;
}

int main(void)
{
    double S, v, a, b, x;
    v = 0.1;
    x = 1;
    b = 100;
    for (a = b - 0.01; a > 0; a -= 0.01) {
        S = SimpInt2(1000, a, b);
        printf("a = %0.10f Simpson = %8g\n",a ,S);
        if (S > ERR){
            x = a;
            break;
        }
    }
    
    int n;
    S = 0;
    b = -x;
	for (n = 10; n <= 1e+7; n *= 10){
		S = SimpInt(n, b, x, v);
		printf("n = %8d Simpson = %lf\n",n ,1 - S);
	}

    
    return 0;
}
