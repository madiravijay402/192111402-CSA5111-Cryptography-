#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext, char *key) {
    int keyLen = strlen(key);
    int textLen = strlen(plaintext);

    for (int i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char shift = tolower(key[i % keyLen]) - 'a';
            char base = islower(plaintext[i]) ? 'a' : 'A';

            plaintext[i] = (plaintext[i] - base + shift) % 26 + base;
        }
    }
}

int main() {
    char plaintext[100];
    char key[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    // Remove newline characters
    plaintext[strcspn(plaintext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    encrypt(plaintext, key);

    printf("Encrypted message: %s\n", plaintext);

    return 0;
}
