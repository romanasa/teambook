const double GOLDEN = (sqrt(5) - 1) / 2;
const double eps = 1e-7; // 2.4 times faster than 3-search
double gss(double a, double b, function<double(double)> f) {
    double x1 = b - GOLDEN * (b - a), x2 = a + GOLDEN * (b - a);
    double f1 = f(x1), f2 = f(x2);
    while (b - a > eps) if (f1 < f2) { //change to > to find maximum
        b = x2; x2 = x1; f2 = f1; x1 = b - GOLDEN * (b - a);f1 = f(x1);
    } else {
        a = x1; x1 = x2; f1 = f2; x2 = a + GOLDEN * (b - a); f2 = f(x2);
    }
    return a;
}