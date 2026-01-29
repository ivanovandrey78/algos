#include "math_functions.h"

namespace algs {

namespace math {

// Newton's approximation (recursion)
double sqrtNewton(double n,int maxIterations) {
    if (n < 0) { std::cerr << "Number must be positive" << '\n'; return 1; }
    if (n == 1) return 1.0;
    if (n == 0) return 0.0;
    
    if (maxIterations <= 0) {
        int d = 1;
        while (d*d <= n) {
            if (d * d == n) return static_cast<double>(d);
            d++;
        }
        d--;
        double derivative = 1.0/(2.0*d);
        return d + (n - d * d) * derivative;
    }

    double currentApprox = sqrtNewton(n, maxIterations-1);
    
    double derivative = 1.0/(2.0*currentApprox);
    double result = currentApprox + (n - currentApprox*currentApprox)*derivative;
    
    return result;
}

// BinarySearch on real numbers

int min(int a,int b) { return (a <= b) ? a : b; }

int max(int a,int b) { return (a >= b) ? a : b; }

double pow (double n,int rec) {
    double prod = 1;
    for (int i = 0; i < rec; ++i) prod *= n;
    return prod;
}

// Rounding
double round(double x) {
    if (x >= 0.0) {
        return static_cast<long long>(x + 0.5);
    } else {
        return static_cast<long long>(x - 0.5);
    }
}

double floor(double x) {
    double result = static_cast<long long>(x);
    if (x < 0.0 && x != result) result -= 1.0; 
    return result;
}

double ceil(double x) {
    double result = static_cast<long long>(x);
    if (x > 0.0 && x != result) result += 1.0;
    return result;
}

double trunc(double x) { return static_cast<long long>(x); }

// Math functions
unsigned long factorial(unsigned int n) {
    unsigned long result = (n == 0) ? 1 : n * factorial(n-1);
    return result;
}

double ln(double x) {
    if (x <= 0) { 
        throw "ln(x) undefined for x <= 0"; 
    }
    
    int m = 0;
    double s = x;
    
    while (s >= 2.0) {
        s /= 2.0;
        m++;
    }
    while (s < 1.0) {
        s *= 2.0;
        m--;
    }

    double t = (s - 1.0) / (s + 1.0);
    double t_sq = t * t;
    double term = t;
    double sum = term;
    
    for (int k = 1; k <= 20; k++) {
        term *= t_sq;
        double new_term = term / (2*k + 1);
        sum += new_term;
        
        if (new_term < 1e-16) break;
    }
    
    return 2.0 * sum + m * LN2;
}

bool isPrime(int n) { 
    bool flag = true;
    for (int d = 2; d < sqrtNewton(n); d++) {
        if (n%d == 0) flag = false;
    }
    return flag;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

double arctan(double x) {
    if (x > 1.0)
        return PI_2 - arctan(1.0 / x);
    if (x < -1.0)
        return -PI_2 - arctan(1.0 / x);

    if (x > 0.0) {
        double t = (x - 1.0) / (x + 1.0);
        double t2 = t * t;
        double sum = 0.0;
        double term = t;
        int sign = 1;

        for (int n = 0; n < 50; ++n) {
            sum += sign * term / (2 * n + 1);
            term *= t2;
            sign = -sign;
        }

        return PI_4 + 2.0 * sum;
    }

    return -arctan(-x);
}

double arctan2(double y, double x) {
    if (x == 0.0) {
        if (y == 0.0) return 0.0;
        return (y > 0.0) ? PI_2 : -PI_2;
    }

    double ratio = y / x;
    double angle = arctan(ratio);

    if (x < 0.0) {
        if (y >= 0.0) angle += PI;
        else angle -= PI;
    }
    return angle;
}

} // namespace math 

} // namespace algs