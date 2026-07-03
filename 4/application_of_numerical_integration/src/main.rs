const ERR: f64 = 1e-12;
const PI: f64 = std::f64::consts::PI;
// #![feature(float_erf)]

fn main() {
    let v = 0.1;
    let mut b = 100.0;
    let mut x = 1.0;

    let mut a = b - 0.01;
    while a > 0.0 {
        let s = simpson(1000, a, b);
        // let s = (a / 2.0_f64.sqrt()).erf();
        println!("a = {a:.2} Simpson = {s:.13}");
        if s > ERR {
            x = a;
            break;
        }
        a -= 0.01;
    }

    let mut n = 10;
    b = -x;

    println!("Integral range: [{b:.2}, {x:.2}]");
    while n <= 10_000_000 {
        let s = simpson2(n, b, x, v);
        let result = 1.0 - s;

        println!("n{n:8} Simpson={result:.6}");
        n *= 10;
    }
}

fn integrand(x: f64) -> f64 {
    2.0 * (-x * x / 2.0).exp() / (2.0 * PI).sqrt()
}

fn integrand2(x: f64, v: f64) -> f64 {
    let t = (x / (v).sqrt() + 1.0 / v).tanh();

    t * t * (-x * x / 2.0).exp() / (2.0 * PI).sqrt()
}

fn simpson(n: i32, a: f64, b: f64) -> f64 {
    let h = (b - a) / f64::from(n);
    let sum = (0..n).fold(0.0, |acc, i| {
        let i = f64::from(i);

        acc + integrand(i * h + a)
            + 4.0 * integrand((i + 0.5) * h + a)
            + integrand((i + 1.0) * h + a)
    });

    sum * h / 6.0
}

fn simpson2(n: i32, a: f64, b: f64, v: f64) -> f64 {
    let h = (b - a) / f64::from(n);
    let sum = (0..n).fold(0.0, |acc, i| {
        let i = f64::from(i);

        acc + integrand2(i * h + a, v)
            + 4.0 * integrand2((i + 0.5) * h + a, v)
            + integrand2((i + 1.0) * h + a, v)
    });

    sum * h / 6.0
}

#[cfg(test)]
mod tests {
    use super::*;

    fn square(x: f64) -> f64 {
        x * x
    }

    fn simpson_on<F: Fn(f64) -> f64>(n: i32, a: f64, b: f64, f: F) -> f64 {
        let h = (b - a) / f64::from(n);
        let sum = (0..n).fold(0.0, |acc, i| {
            let i = f64::from(i);
            acc + f(i * h + a) + 4.0 * f((i + 0.5) * h + a) + f((i + 1.0) * h + a)
        });
        sum * h / 6.0
    }

    #[test]
    fn simpson_integrates_x_squared() {
        let result = simpson_on(1000, 0.0, 1.0, square);
        assert!((result - 1.0 / 3.0).abs() < 1e-8);
    }
}
