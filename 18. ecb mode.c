#include <stdio.h>
#include <string.h>

// Simulated encryption function (XOR operation)
void encrypt(char* plaintext, char* iv, char* ciphertext, int block_size) {
    for (int i = 0; i < block_size; i++) {
        ciphertext[i] = plaintext[i] ^ iv[i];
    }
}

// Simulated decryption function (XOR operation)
void decrypt(char* ciphertext, char* iv, char* plaintext, int block_size) {
    for (int i = 0; i < block_size; i++) {
        plaintext[i] = ciphertext[i] ^ iv[i];
    }
}

int main() {
    int block_size = 8;  // Assuming an 8-byte block size
    char P1[block_size] = "BlockP1";  // Original P1
    char P2[block_size] = "BlockP2";  // Original P2
    char C1[block_size];
    char C2[block_size];
    char IV[block_size] = "RandomIV";

    // Encrypt P1 with CBC using IV
    encrypt(P1, IV, C1, block_size);

    // Simulate a bit error in the source version of P1
    P1[2] ^= 0x01;  // Flip a bit in P1

    // Encrypt the modified P1 with CBC using IV
    encrypt(P1, IV, C2, block_size);

    // Decrypt C1 with CBC using IV
    char decrypted_P1[block_size];
    decrypt(C1, IV, decrypted_P1, block_size);

    // Decrypt C2 with CBC using IV
    char decrypted_P2[block_size];
    decrypt(C2, IV, decrypted_P2, block_size);

    // Print the results
    printf("Original P1: %s\n", P1);
    printf("Ciphertext C1: %s\n", C1);
    printf("Decrypted P1: %s\n", decrypted_P1);
    printf("Ciphertext C2: %s\n", C2);
    printf("Decrypted P2: %s\n", decrypted_P2);

    return 0;
}
