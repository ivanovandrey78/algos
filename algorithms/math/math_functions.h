#pragma once 

#include <iostream>
#include <string>

namespace algs {

namespace math {
    // math constants
    constexpr double PI = 3.141592653589793238462643383279502884197169399375105820974944;
    constexpr double E = 2.718281828459045235360287471352662497757247093699959574966967;
    constexpr double LN2 = 0.693147180559945309417232121458176568075500134360255254120680;
    const double PI_2 = PI/2;
    const double PI_4 = PI/4;
    const double PI_6 = PI/6;
    const double PI_3 = PI/3;
    
    // ranks and combinatorial functions
    unsigned long factorial(unsigned int n);
    
    // operations on two variables
    int gcd(int a, int b);
    int min(int a, int b); 
    int max(int a, int b);
    
    // advanced math operations
    double arctan(double x);
    double arctan2(double y, double x);
    double sqrtNewton(double n, int maxIterations = 3);   
    double ln(double x);
    double pow(double n, int rec);
    
    // check 
    bool isPrime(int n);

    // rouding
    double round(double x);
    double floor(double x);
    double ceil(double x);
    double trunc(double x);
} // namespace math 

} // namespace algs