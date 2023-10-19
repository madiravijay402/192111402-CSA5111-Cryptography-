#include <stdio.h>
#include <openssl/rsa.h>

int main() {
    RSA *rsa;

    // Generate a new RSA key pair with a specified key length (e.g., 2048 bits)
    rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);

    // Output the public key (n and e) and private key (d)
    printf("New Public Key (n, e): (%s, %s)\n", BN_bn2hex(rsa->n), BN_bn2hex(rsa->e));
    printf("New Private Key (d): %s\n", BN_bn2hex(rsa->d));

    // Don't forget to free the RSA structure when done
    RSA_free(rsa);

    return 0;}
