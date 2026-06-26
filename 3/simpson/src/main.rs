fn integrand(x: f64) -> f64 {
    1.0 / (1.0 + x)
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

fn main() {
    let a = 0.0;
    let b = 1.0;
    let expected = 2.0_f64.ln();
    let mut n = 10;

    while n <= 10_000_000 {
        let area = simpson(n, a, b);
        let error = ((area - expected) / expected).abs();

        println!("n{n:8} Simpson={area:.6} error={error:.20}");
        n *= 10;
    }
}
