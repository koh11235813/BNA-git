# BNA-git
this project is sample and report program for Fundamental Numeric Analysis

## 01 Active Learning 1
```C
#include <stdio.h>
int main()
{
    printf("Helo World");
}
```
## 02 Compute the following summation with Horner’s method, and answer the absolute error between S_10(1) and exp(1).
$ S_n(x) = \Sigma^n_{k = 0}\frac{x^k}{k!} $

```C
#include<stdio.h>
#include<math.h>

int main()
{
    int m,n;
    double x,S;

    n = 10; x = 1.0;

    S = 1.0;
    for(m=n;m>0;m--) {
        S = 1.0+x*S/(double)m;
    }

    printf("|S-exp(x)|=%g for n=%d and x=%g¥n",fabs(S-exp(1.0)),n,x);
}
```

## 03 Answer quantitatively the changes of the relative errors between the analytical solution $S_0$ and the numerical solutions as the number � of subintervals increases.

$ S_0 = \int^2_0\frac{1}{1+x}dx. $
\
Simpsons' Rule
```C
double SimpInt(int n,double a,double b)
{
    int i;
    double S,h;

    S = 0.0; h = (b-a)/(double)n;
    for(i=0;i<n;i++) {
        S += func(i*h+a) + 4.0*func((i+0.5)*h+a)
        + func((i+1.0)*h+a);
    }
    S *= h/6.0;

    return S;
}
```
\
main function
```C
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    int n;
    double a,b,S,S0,err;

    S0 = log(2.0); a = 0.0; b = 1.0;
    for(n=10;n<=1e+7;n*=10) {
        S = SimpInt(n,a,b); err = fabs((S-S0)/S0);
        printf("n=%8d Simpson=%g error=%g¥n",n,S,err);
    }
}
```
\
Example Result
```
n= 10 Simpson=0.693147 error=2.80035e-07
n= 100 Simpson=0.693147 error=2.81759e-11
n= 1000 Simpson=0.693147 error=4.80514e-16
n= 10000 Simpson=0.693147 error=4.00428e-15
n= 100000 Simpson=0.693147 error=5.12548e-15
n= 1000000 Simpson=0.693147 error=5.44583e-15
n=10000000 Simpson=0.693147 error=8.12069e-14
```

## 04 Compute MSE(0.1) numerically.
$ MSE(v) = 1-\int^{\infty}_{-\infty}\tanh^2\left(\frac{x}{\sqrt{v}}+\frac{1}{v}\right)\frac{1}{\sqrt{2\pi}}e^{-\frac{x^2}{2}}dx $
\
Integrand
```C
double func(double x,double v)
{
    double t;

    t = tanh(x/sqrt(v) + 1.0/v);
    return t*t*exp(-x*x/2.0)/sqrt(2.0*M_PI);
}
```

Upperbound
$ \int^a_{-a}\tanh^2\left(\frac{x}{\sqrt{v}}+\frac{1}{v}\right)\frac{1}{\sqrt{2\pi}}e^{-\frac{x^2}{2}}dx \ｌ