#include <stdio.h>
#include <math.h>

#define ERR 1.0e-13
#define EPS 1.0e-11
#define SIGMA2 0.1
#define ALPHA 1.8

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

double MSE(int n, double b, double x, double v)
{
    return 1- SimpInt(n, x, b, v);
}

double function(int n, double b, double x,double v)
{
    return SIGMA2+ALPHA*MSE(n, x, b, v) - v;
}

double mseBisection(int n, double b, double x, double vl0, double vr0)
{
    int i, number;
    double v, vl, vr, vs, yl_sign;

    number = 10000;
    vl = vl0;
    vr = vr0;

    yl_sign = function(n, b, x, vl0);
    for (i = 1; i <= number; i++) {
        v = (vl + vr)/2.0;
        printf("Iteration = %d, solution = %g, error = %g \n", i, v, fabs(function(n, b, x, vl) - function(n, b, x, vr)));
        if(yl_sign*function(n, b, x, v) > 0.0) {
            vl = v;
        }else{
            vr = v;
        }
        if (vr - vl < EPS){
            return v;
        }
    }
    return -1;
}

int main(void)
{
    double S, v, a, b, x;
    double vl0, vr0, mse1;

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
    double dump = 0;
	for (n = 10; n <= 1e+7; n *= 10){
		S = SimpInt(n, b, x, v);
		printf("n = %8d Simpson = %lf\n",n ,1 - S);
		if (fabs(dump - (1 - S)) < ERR){
		  break;
		}
		dump = 1-S;
	}
	//ここまででシンプソン法でMSE(v)のn, x, bが定まり，あとはvを求めるだけ
	//ここでvは**0.1**にされている
	printf("dump:%1.8f\nn:%d\nx:%f\nb:%f\n", dump, n, x, b);

	printf("xl0:");
    scanf("%lf",&vl0);

    printf("xr0:");
    scanf("%lf",&vr0);

    mse1 = mseBisection(n, b, x, vl0, vr0);
    printf("1. %1.8f\n", mse1);

}
