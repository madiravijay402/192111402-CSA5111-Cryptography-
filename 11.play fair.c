#include <stdio.h>
#include <math.h>

int main() {
    double n = 25.0;
    double approx_key_count = pow(n, n) * exp(-n) * sqrt(2 * M_PI * n);

    printf("Approximate number of possible Playfair cipher keys: %.0f\n", approx_key_count);

    return 0;
}
