#include <stdio.h>
#include <math.h>

// 被積分関数の定義
double func(double x, double v) {
    double t = tanh(x / sqrt(v) + 1.0 / v);
    return t * t * exp(-x * x / 2.0) / sqrt(2.0 * M_PI);
}

// シンプソン法を使用して数値積分を計算する関数
double SimpInt(int n, double a, double b, double v) {
    int i;
    double S, h;
    S = 0.0;
    h = (b - a) / (double)n;
    for (i = 0; i < n; i++) {
        S += func(i * h + a, v) + 4.0 * func((i + 0.5) * h + a, v) + func((i + 1.0) * h + a, v);
    }
    S *= h / 6.0;
    return S;
}

// 誤差評価のための関数
double error_estimation(double a) {
    return 1.0 - erf(a / sqrt(2.0));
}

int main() {
    double v = 0.1;
    double a = 1.0; // 初期の積分区間の上限
    int n = 5000;  // 分割数
    double tolerance = 1e-5; // 許容誤差

    // 誤差が十分小さいかどうかを確認しながら積分区間を調整
    while (error_estimation(a) > tolerance) {
        a += 1.0;
    }

    // 数値積分を計算
    double integral = SimpInt(n, -a, a, v);

    // MSE(v)を計算
    double mse = 1.0 - integral;

    // 結果を表示
    printf("MSE(%.1f) = %.10f\n", v, mse);
    printf("Integral range: [-%.1f, %.1f]\n", a, a);
    printf("Estimated error: %.10f\n", error_estimation(a));
    printf("Final value of a: %.1f\n", a);

    return 0;
}
