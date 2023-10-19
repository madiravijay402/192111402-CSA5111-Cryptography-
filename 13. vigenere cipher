#include <stdio.h>
#include <string.h>

// Function to encrypt the plaintext using the one-time pad Vigenère cipher
void encrypt(char* plaintext, char* key, char* ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        ciphertext[i] = (plaintext[i] - 'a' + (key[i] - 'a')) % 26 + 'a';
    }
    ciphertext[len] = '\0';
}

// Function to decrypt the ciphertext using the one-time pad Vigenère cipher
void decrypt(char* ciphertext, char* key, char* plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        plaintext[i] = (ciphertext[i] - 'a' - (key[i] - 'a') + 26) % 26 + 'a';
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[] = "sendmoremoney";
    char key[] = "90172315211411289";
    char ciphertext[strlen(plaintext) + 1];

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    char target[] = "cashnotneeded";
    char candidateKey[strlen(key) + 1];
    char decryptedText[strlen(plaintext) + 1];

    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < strlen(key); i++) {
            candidateKey[i] = (key[i] - '0' + k) % 26 + '0';
        }
        candidateKey[strlen(key)] = '\0';
        decrypt(ciphertext, candidateKey, decryptedText);
        
        if (strcmp(decryptedText, target) == 0) {
            printf("Found Key: %s\n", candidateKey);
            break;
        }
    }

    return 0;
}
