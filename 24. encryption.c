#include <stdio.h>
#include <string.h>

int main() {
    char ciphertext[] = "CIPHERTEXT"; // Replace with the actual ciphertext
    int i, j;
    int frequency[26] = {0};
    char decrypted[100]; // Assuming a maximum message length of 100 characters

    for (i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            frequency[ciphertext[i] - 'A']++;
        }
    }

    for (i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int maxFreq = 0;
            int decryptedChar = 0;
            for (j = 0; j < 26; j++) {
                if (frequency[j] > maxFreq) {
                    maxFreq = frequency[j];
                    decryptedChar = 'A' + j;
                }
            }
            decrypted[i] = decryptedChar;
            frequency[decryptedChar - 'A'] = 0; // Remove the character from consideration
        } else {
            decrypted[i] = ciphertext[i];
        }
    }

    decrypted[i] = '\0'; // Null-terminate the decrypted message
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}
