#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {
    // Initialization Vector (IV) and Key (24 bytes for 3DES)
    unsigned char iv[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    unsigned char key[] = "ThisIs24BytesFor3DESKey";

    const char* plaintext = "Hello, CBC encryption!";
    int plaintext_len = strlen(plaintext);

    // Initialize OpenSSL cipher context
    EVP_CIPHER_CTX *ctx;
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        handleErrors();
    }

    // Initialize 3DES-CBC encryption
    if (1 != EVP_EncryptInit_ex(ctx, EVP_des_ede3_cbc(), NULL, key, iv)) {
        handleErrors();
    }

    // Buffer to hold the ciphertext
    unsigned char ciphertext[128]; // Make sure it's large enough

    int ciphertext_len;
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &ciphertext_len, (const unsigned char *)plaintext, plaintext_len)) {
        handleErrors();
    }

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + ciphertext_len, &ciphertext_len)) {
        handleErrors();
    }
    ciphertext_len += ciphertext_len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    // Print the ciphertext
    printf("Ciphertext: ");
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
6) Write a C program for ECB mode, if there is an error in a block of the
transmitted ciphertext, only the corresponding plaintext block is affected.
However, in the CBC mode, this error propagates. For example, an error in the
transmitted C1 obviously corrupts P1 and P2.

a. Are any blocks beyond P2 affected?
b. Suppose that there is a bit error in the source version of P1. Through how many
ciphertext blocks is this error propagated? What is the effect at the receiver?
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt(char* plaintext, char* ciphertext, int block_size) {
    // Implement your encryption logic here (e.g., using a strong encryption algorithm)
    // For simplicity, we use a simple XOR operation to simulate encryption
    for (int i = 0; i < block_size; i++) {
        ciphertext[i] = plaintext[i] ^ 0x55;  // Simulated encryption
    }
}

void decrypt(char* ciphertext, char* plaintext, int block_size) {
    // Implement your decryption logic here (matching the encryption process)
    for (int i = 0; i < block_size; i++) {
        plaintext[i] = ciphertext[i] ^ 0x55;  // Simulated decryption
    }
}

int main() {
    int block_size = 8;  // Assuming an 8-byte block size
    char P1[block_size] = "BlockP1"; // Original P1
    char P2[block_size] = "BlockP2"; // Original P2
    char C1[block_size];
    char C2[block_size];

    // Encrypt P1
    encrypt(P1, C1, block_size);

    // Simulate an error in P1
    P1[1] = 'X'; // Replace a character in P1 with 'X'

    // Encrypt the modified P1
    encrypt(P1, C2, block_size);

    // Decrypt C1
    char decrypted_P1[block_size];
    decrypt(C1, decrypted_P1, block_size);

    // Decrypt C2
    char decrypted_P2[block_size];
    decrypt(C2, decrypted_P2, block_size);

    // Print the results
    printf("Original P1: %s\n", P1);
    printf("Ciphertext C1: %s\n", C1);
    printf("Decrypted P1: %s\n", decrypted_P1);
    printf("Ciphertext C2: %s\n", C2);
    printf("Decrypted P2: %s\n", decrypted_P2);

    return 0;
}

