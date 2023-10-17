#include <stdio.h>
#include <string.h>

#define MATRIX_SIZE 5

void createPlayfairMatrix(char key[], char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int keyLength = strlen(key);
    int alphabet[26] = {0}; // to keep track of which letters have been used
    int row = 0, col = 0;

    // Initialize the matrix with zeros
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = 0;
        }
    }

    // Process the key
    for (int i = 0; i < keyLength; i++) {
        char c = key[i];
        if (c == 'J') // Combine 'I' and 'J'
            c = 'I';

        if (alphabet[c - 'A'] == 0) {
            matrix[row][col] = c;
            alphabet[c - 'A'] = 1;
            col++;

            if (col == MATRIX_SIZE) {
                col = 0;
                row++;
            }
        }
    }

    // Fill the remaining matrix with unused letters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c != 'J' && alphabet[c - 'A'] == 0) {
            matrix[row][col] = c;
            col++;

            if (col == MATRIX_SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

void findPositions(char matrix[MATRIX_SIZE][MATRIX_SIZE], char c, int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void playfairEncrypt(char matrix[MATRIX_SIZE][MATRIX_SIZE], char plainText[], char cipherText[]) {
    int length = strlen(plainText);
    int pos1_row, pos1_col, pos2_row, pos2_col;

    for (int i = 0, j = 0; i < length; i += 2) {
        char c1 = plainText[i];
        char c2 = (i + 1 < length) ? plainText[i + 1] : 'X'; // Add 'X' for odd-length messages

        findPositions(matrix, c1, &pos1_row, &pos1_col);
        findPositions(matrix, c2, &pos2_row, &pos2_col);

        if (pos1_row == pos2_row) {
            cipherText[j++] = matrix[pos1_row][(pos1_col + 1) % MATRIX_SIZE];
            cipherText[j++] = matrix[pos2_row][(pos2_col + 1) % MATRIX_SIZE];
        } else if (pos1_col == pos2_col) {
            cipherText[j++] = matrix[(pos1_row + 1) % MATRIX_SIZE][pos1_col];
            cipherText[j++] = matrix[(pos2_row + 1) % MATRIX_SIZE][pos2_col];
        } else {
            cipherText[j++] = matrix[pos1_row][pos2_col];
            cipherText[j++] = matrix[pos2_row][pos1_col];
        }
    }

    cipherText[length] = '\0';
}

int main() {
    char key[] = "MFHIJKUNOPQZVWXYELARGBDSTBC";
    char plainText[] = "MUST SEE YOU OVER CADOGAN WEST COMING AT ONCE";
    char cipherText[100] = {0};
    char playfairMatrix[MATRIX_SIZE][MATRIX_SIZE];

    createPlayfairMatrix(key, playfairMatrix);
    playfairEncrypt(playfairMatrix, plainText, cipherText);

    printf("Original Message: %s\n", plainText);
    printf("Encrypted Message: %s\n", cipherText);

    return 0;
}
