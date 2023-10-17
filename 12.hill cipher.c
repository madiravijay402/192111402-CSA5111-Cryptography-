#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Alphabet size
#define ALPHABET_SIZE 26

// Function to convert a character to its corresponding integer value
int charToInt(char c) {
  return c - 'A';
}

// Function to convert an integer value to its corresponding character
char intToChar(int i) {
  return i + 'A';
}

// Function to multiply two matrices
void multiplyMatrices(int **a, int **b, int **c, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      c[i][j] = 0;
      for (int k = 0; k < n; k++) {
        c[i][j] += (a[i][k] * b[k][j]) % ALPHABET_SIZE;
      }
      c[i][j] %= ALPHABET_SIZE;
    }
  }
}

// Function to find the inverse of a matrix
int **findInverseMatrix(int **a, int n) {
  int **b = malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    b[i] = malloc(n * sizeof(int));
  }

  // Get the determinant of the matrix
  int determinant = 1;
  for (int i = 0; i < n; i++) {
    determinant *= a[i][i];
  }

  // If the determinant is 0, the matrix is not invertible
  if (determinant == 0) {
    return NULL;
  }

  // Calculate the adjugate of the matrix
  int **adjugate = malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    adjugate[i] = malloc(n * sizeof(int));
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int **cofactor = malloc((n - 1) * sizeof(int *));
      for (int k = 0; k < n - 1; k++) {
        cofactor[k] = malloc((n - 1) * sizeof(int));
      }

      int minor = 1;
      for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
          if (x != i && y != j) {
            cofactor[x][y] = a[x][y];
            minor *= a[x][y];
          }
        }
      }

      adjugate[i][j] = minor * pow(-1, i + j);

      for (int k = 0; k < n - 1; k++) {
        free(cofactor[k]);
      }
      free(cofactor);
    }
  }

  // Multiply the adjugate by the determinant to get the inverse matrix
  multiplyMatrices(adjugate, determinant, b, n);

  // Free the temporary matrices
  for (int i = 0; i < n; i++) {
    free(adjugate[i]);
  }
  free(adjugate);

  return b;
}

// Function to encrypt a plaintext message using the Hill cipher
int *encrypt(char *plaintext, int **key, int n) {
  int *ciphertext = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    ciphertext[i] = 0;
    for (int j = 0; j < n; j++) {
      ciphertext[i] += ((charToInt(plaintext[i]) * key[i][j]) % ALPHABET_SIZE);
    }
    ciphertext[i] %= ALPHABET_SIZE;
  }

  return ciphertext;
}
