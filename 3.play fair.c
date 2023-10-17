#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char keyMatrix[SIZE][SIZE];

void prepareKey(char *key) {
    int i, j, k;
    char ch = 'A';
    int used[26] = {0};

    for (i = 0; i < strlen(key); i++) {
        if (key[i] == 'J')
            key[i] = 'I';
        if (!used[key[i] - 'A']) {
            keyMatrix[i / SIZE][i % SIZE] = key[i];
            used[key[i] - 'A'] = 1;
        }
    }

    for (k = 0; k < 26; k++) {
        if (k + 'A' != 'J' && !used[k]) {
            keyMatrix[i / SIZE][i % SIZE] = k + 'A';
            used[k] = 1;
            i++;
        }
    }
}

void findPosition(char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';
    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (keyMatrix[*row][*col] == ch)
                return;
        }
    }
}

void encryptPair(char a, char b) {
    int rowA, colA, rowB, colB;
    findPosition(a, &rowA, &colA);
    findPosition(b, &rowB, &colB);

    if (rowA == rowB) {
        colA = (colA + 1) % SIZE;
        colB = (colB + 1) % SIZE;
    } else if (colA == colB) {
        rowA = (rowA + 1) % SIZE;
        rowB = (rowB + 1) % SIZE;
    } else {
        int temp = colA;
        colA = colB;
        colB = temp;
    }

    printf("%c%c", keyMatrix[rowA][colA], keyMatrix[rowB][colB]);
