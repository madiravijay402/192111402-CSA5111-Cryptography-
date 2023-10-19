#include <stdio.h>
#include <stdint.h>

// S-DES Key
uint8_t sdes_key[10] = {0, 1, 1, 1, 1, 1, 1, 0, 1, 0};

// S-DES S-Box Definitions
uint8_t sdes_sbox0[4][4] = {{1, 0, 3, 2},
                           {3, 2, 1, 0},
                           {0, 2, 1, 3},
                           {3, 1, 3, 2}};

uint8_t sdes_sbox1[4][4] = {{0, 1, 2, 3},
                           {2, 0, 1, 3},
                           {3, 0, 1, 0},
                           {2, 1, 0, 3}};

// S-DES Permutation P4
uint8_t sdes_p4[4] = {1, 3, 2, 0};

// S-DES Expansion P4
uint8_t sdes_ep[4] = {3, 0, 1, 2};

// S-DES Permutation P10
uint8_t sdes_p10[10] = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5};

// S-DES Left Shifts for Key Generation
int sdes_shifts[2] = {1, 2};

// Function to perform a permutation on data using the given permutation array
void sdes_permute(uint8_t* data, const uint8_t* perm, int size) {
    uint8_t temp[size];
    for (int i = 0; i < size; i++) {
        temp[i] = data[perm[i]];
    }
    for (int i = 0; i < size; i++) {
        data[i] = temp[i];
    }
}

// Function to perform S-DES substitution using the given S-Box
uint8_t sdes_substitute(uint8_t data, const uint8_t sbox[4][4]) {
    uint8_t row = (data & 0x02) >> 1 | (data & 0x01);
    uint8_t col = (data & 0x0C) >> 2 | (data & 0x04) >> 1;
    return sbox[row][col];
}

// Function to perform S-DES key generation
void sdes_generate_keys(uint8_t* key, uint8_t* k1, uint8_t* k2) {
    sdes_permute(key, sdes_p10, 10);

    // Split the key into left and right halves
    uint8_t left_half[5], right_half[5];
    for (int i = 0; i < 5; i++) {
        left_half[i] = key[i];
        right_half[i] = key[i + 5];
    }

    // Perform left shifts
    for (int i = 0; i < 2; i++) {
        uint8_t temp_left = left_half[0];
        uint8_t temp_right = right_half[0];
        for (int j = 0; j < 4; j++) {
            left_half[j] = left_half[j + 1];
            right_half[j] = right_half[j + 1];
        }
        left_half[4] = temp_left;
        right_half[4] = temp_right;
    }

    // Combine left and right halves
    for (int i = 0; i < 5; i++) {
        key[i] = left_half[i];
        key[i + 5] = right_half[i];
    }

    // Generate K1
    sdes_permute(key, sdes_p8, 8);
    for (int i = 0; i < 8; i++) {
        k1[i] = key[i];
    }

    // Perform left shifts again for K2
    for (int i = 0; i < 2; i++) {
        uint8_t temp_left = left_half[0];
        uint8_t temp_right = right_half[0];
        for (int j = 0; j < 4; j++) {
            left_half[j] = left_half[j + 1];
            right_half[j] = right_half[j + 1];
        }
        left_half[4] = temp_left;
        right_half[4] = temp
