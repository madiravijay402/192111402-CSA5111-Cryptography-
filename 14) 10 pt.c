#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to calculate the frequency of letters in a string
void calculateLetterFrequency(const char *text, int frequency[26]) {
    for (int i = 0; i < strlen(text); i++) {
        char c = tolower(text[i]);
        if (isalpha(c)) {
            frequency[c - 'a']++;
        }
    }
}

// Function to decrypt the ciphertext with a given shift value
void decryptWithShift(const char *ciphertext, int shift, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            plaintext[i] = (c - shift - base + 26) % 26 + base;
        } else {
            plaintext[i] = c;
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char ciphertext[] = "Gur dhvpx oebja sbeg vf zl ubg!";
    int frequency[26] = {0};
    calculateLetterFrequency(ciphertext, frequency);

    // Find the most common letter in the ciphertext
    int maxFrequency = 0;
    char mostCommonLetter;
    for (int i = 0; i < 26; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            mostCommonLetter = 'a' + i;
        }
    }

    // Determine the shift value based on the most common letter (e.g., 'e' -> 4)
    int shift = mostCommonLetter - 'e';
    
    char plaintext[strlen(ciphertext) + 1];
    decryptWithShift(ciphertext, shift, plaintext);

    printf("Shift used for decryption: %d\n", shift);
    printf("Decrypted Plaintext: %s\n", plaintext);

    return 0;
}
