#include <stdio.h>
#include <math.h>

#define EPS 1.0e-15

double Function(double x)
{
    return x*x*x-x;
}

void Bisection(double xl0, double xr0)
{
    int i, number;
    double x, xl, xr, xs, yl_sign;

    number = 10000;
    xl = xl0;
    xr = xr0;
    xs = 0.0;

    yl_sign = Function(xl0);
    for (i = 1; i <= number && xr - xl > EPS; i++) {
        x = (xl + xr)/2.0;
        printf("Iteration = %d, solution = %g, error = %g \n", i, x, fabs(x - xs));
        if(yl_sign*Function(x) > 0.0) {
            xl = x;
        }else{
            xr = x;
        }
    }
}
int main(void)
{
    int i, j;
    double xl0, xr0;

    printf("xl0:");
    scanf("%lf",&xl0);

    printf("xr0:");
    scanf("%lf",&xr0);

/*
    for (i = 0; i <=10; i++){
        //xl0 = -1 + 0.1 * i;
        //xr0 = -xl0;

        for (j = 0; j < 10; j++){
            xr0 = 1 - 0.1*i - 0.01*j;
            xl0 = -xr0-0.03;

            printf("xl0 = %f, xr0 = %f\n", xl0, xr0);
            Bisection(xl0, xr0);
            puts("end");
        }
        */
        /*
        printf("xl0 = %f, xr0 = %f\n", xl0, xr0);
        Bisection(xl0, xr0);
        puts("end");
        */
//    }
    /*
    for (i = 1; i <=10; i++){
        xl0 = -0.1 + 0.01 * i;
        xr0 = -xl0;

        printf("xl0 = %f, xr0 = %f\n", xl0, xr0);
        Bisection(xl0, xr0);
        puts("end");
    }
    */

    Bisection(xl0, xr0);
    return 0;
}