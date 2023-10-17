#include <stdio.h>
#include <string.h>
#include <ctype.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

int decrypt(int a, int b, int c) {
    int aInverse = modInverse(a, 26);
    return (aInverse * (c - b + 26)) % 26;
}

int main() {
    char ciphertext[100];
    int mostFrequentLetter = 'B' - 'A';  // Assuming uppercase letters
    int secondMostFrequentLetter = 'U' - 'A';  // Assuming uppercase letters

    printf("Enter the ciphertext: ");
    scanf(" %[^\n]", ciphertext);

    for (int a = 1; a < 26; a++) {
        int aInverse = modInverse(a, 26);
        for (int b = 0; b < 26; b++) {
            int valid = 1;
            char decrypted[100];
            strcpy(decrypted, ciphertext);

            for (int i = 0; decrypted[i] != '\0'; i++) {
                if (isalpha(decrypted[i])) {
                    char base = islower(decrypted[i]) ? 'a' : 'A';
                    int c = decrypted[i] - base;
                    int p = decrypt(a, b, c);
                    decrypted[i] = p + base;

                    if (p == mostFrequentLetter) {
                        // Check if the decryption result matches the most frequent letter
                        valid = 0;
                        break;
                    }
                }
            }

            if (valid) {
                printf("Potential key found: a = %d, b = %d\n", a, b);
                printf("Decrypted message: %s\n", decrypted);
            }
        }
    }

    return 0;
}
