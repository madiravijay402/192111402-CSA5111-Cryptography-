#include <stdio.h>
#include <stdint.h>

// Function to perform a circular left shift on a 28-bit block
uint32_t circularLeftShift(uint32_t block, int shift) {
    return (block << shift) | (block >> (28 - shift));
}

// Generate subkeys for DES
void generateSubkeys(uint64_t initialKey, uint32_t subkeys[16]) {
    const int roundShifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    // Initial permutation choice (PC-1) to split the 56-bit key into C0 and D0
    uint32_t C0 = (initialKey >> 28) & 0x0FFFFFFF;
    uint32_t D0 = initialKey & 0x0FFFFFFF;

    for (int round = 0; round < 16; round++) {
        // Perform circular left shift on C and D
        C0 = circularLeftShift(C0, roundShifts[round]);
        D0 = circularLeftShift(D0, roundShifts[round]);

        // Combine C and D to obtain a 56-bit round key
        uint64_t roundKey = ((uint64_t)C0 << 28) | D0;

        // Apply a mask to obtain the 48-bit subkey
        uint32_t subkey = (roundKey >> 20) & 0x0FFFFFFF;

        // Store the subkey
        subkeys[round] = subkey;
    }
}

int main() {
    // Example: Initial 56-bit key
    uint64_t initialKey = 0b11011010000101010110101101011010101011010100110001011010;

    uint32_t subkeys[16];
    generateSubkeys(initialKey, subkeys);

    // Output the subkeys
    for (int round = 0; round < 16; round++) {
        printf("Round %d Subkey: 0x%08X\n", round + 1, subkeys[round]);
    }

    return 0;
}
