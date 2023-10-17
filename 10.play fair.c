#include <stdio.h>
#include <math.h>

int main() {
    double n = 25.0;
    double approx_key_count = pow(n, n) * exp(-n) * sqrt(2 * M_PI * n);

    printf("Approximate number of possible Playfair cipher keys: %.0f\n", approx_key_count);

    return 0;
}
5) Now take into account the fact that some Playfair keys produce the same encryption results. How
many effectively unique keys does the Playfair cipher have?
#include <stdio.h>
#include <string.h>

// Function to prepare the plaintext (make its length even and remove spaces)
void preparePlaintext(char plaintext[], char preparedPlaintext[]) {
    int length = strlen(plaintext);
    int preparedIndex = 0;

    for (int i = 0; i < length; i++) {
        char c = plaintext[i];
        if (c >= 'A' && c <= 'Z') {
            preparedPlaintext[preparedIndex] = c;
            preparedIndex++;
        }
    }

    int extraChars = preparedIndex % 2;  // Ensure the length is even
    for (int i = 0; i < extraChars; i++) {
        preparedPlaintext[preparedIndex] = 'X';
        preparedIndex++;
    }

    preparedPlaintext[preparedIndex] = '\0';
}

// Function to perform Hill encryption
void hillEncrypt(char plaintext[], char keyMatrix[2][2], char ciphertext[]) {
    char preparedPlaintext[1000];
    preparePlaintext(plaintext, preparedPlaintext);

    int length = strlen(preparedPlaintext);
    int keyMatrixInt[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            keyMatrixInt[i][j] = keyMatrix[i][j] - '0';
        }
    }

    int k = 0;
    for (int i = 0; i < length; i += 2) {
        int char1 = preparedPlaintext[i] - 'A';
        int char2 = preparedPlaintext[i + 1] - 'A';
        int result1 = keyMatrixInt[0][0] * char1 + keyMatrixInt[0][1] * char2;
        int result2 = keyMatrixInt[1][0] * char1 + keyMatrixInt[1][1] * char2;

        result1 = (result1 + 26) % 26;
        result2 = (result2 + 26) % 26;

        ciphertext[k] = result1 + 'A';
        ciphertext[k + 1] = result2 + 'A';
        k += 2;
    }

    ciphertext[k] = '\0';
}

int main() {
    char keyMatrix[2][2] = {
        {'9', '4'},
        {'5', '7'}
    };

    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";
    char ciphertext[1000];

    hillEncrypt(plaintext, keyMatrix, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Encrypted Message: %s\n", ciphertext);

    return 0;}
