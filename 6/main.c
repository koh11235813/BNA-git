#include <stdio.h>
#include <math.h>
#define EPS 1.0e-11
#define SIGMA 0.1
#define ALPHA 1.8

double MSE(double v)
{
    return v/(1 + v);
}

double function(double v)
{
    return SIGMA+ALPHA*MSE(v) - v; 
}

double analysis(double v)
{
    return v/ALPHA - SIGMA/ALPHA - v/(1+v);
}
void Bisection(double xl0, double xr0)
{
    int i, number;
    double x, xl, xr, xs, yl_sign;

    number = 10000;
    xl = xl0;
    xr = xr0;
    xs = 0.0;

    yl_sign = analysis(xl0);
    for (i = 1; i <= number && xr - xl > EPS; i++) {
        x = (xl + xr)/2.0;
        printf("Iteration = %d, solution = %g, error = %g \n", i, x, fabs(analysis(xl) - analysis(xl)));
        if(yl_sign*analysis(x) > 0.0) {
            xl = x;
        }else{
            xr = x;
        }
    }
}

void mseBisection(double xl0, double xr0)
{
    int i, number;
    double x, xl, xr, xs, yl_sign;

    number = 10000;
    xl = xl0;
    xr = xr0;

    yl_sign = function(xl0);
    for (i = 1; i <= number && xr - xl > EPS; i++) {
        x = (xl + xr)/2.0;
        printf("Iteration = %d, solution = %g, error = %g \n", i, x, fabs(function(xl) - function(xr)));
        if(yl_sign*function(x) > 0.0) {
            xl = x;
        }else{
            xr = x;
        }
    }
}
int main(void)
{
    int i, j, k;
    double xl0, xr0, mse;

    printf("xl0:");
    scanf("%lf",&xl0);

    printf("xr0:");
    scanf("%lf",&xr0);
    
    puts("\n1.\n");
    mseBisection(xl0, xr0);

    puts("\nanalysis\n");
    Bisection(xl0, xr0);
    return 0;
}