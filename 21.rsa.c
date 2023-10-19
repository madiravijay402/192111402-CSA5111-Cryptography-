#include <stdio.h>
#include <stdint.h>

// Function to calculate the greatest common divisor (GCD) using the extended Euclidean algorithm
int extendedGCD(int a, int b, int* x, int* y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = extendedGCD(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

// Function to calculate the modular multiplicative inverse of a number 'a' modulo 'm'
int modInverse(int a, int m) {
    int x, y;
    int gcd = extendedGCD(a, m, &x, &y);

    if (gcd != 1) {
        printf("Multiplicative inverse does not exist.\n");
        return -1;
    } else {
        // Ensure the result is positive
        int result = (x % m + m) % m;
        return result;
    }
}

int main() {
    // Given public key values
    int e = 31;
    int n = 3599;

    // Calculate p and q (for simplicity, hardcoded values are used here; in practice, you would find these securely)
    int p = 59;
    int q = 61;

    // Calculate phi(n)
    int phi = (p - 1) * (q - 1);

    // Calculate the private key (d)
    int d = modInverse(e, phi);

    if (d != -1) {
        printf("Private key (d): %d\n", d);
    }

    return 0;
}
