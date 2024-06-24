#include <stdio.h>
#include <math.h>
double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}
double doubleFactorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; i += 2) {
        result *= i;
    }
    return result;
}
int main() {
    int key_size = 25;  
    double num_keys = factorial(key_size) / doubleFactorial(key_size / 2);
    double log_base_2 = log2(num_keys); 
    printf("Number of effectively unique keys for Playfair cipher: ~2^%.2f\n", log_base_2);
    return 0;
}

