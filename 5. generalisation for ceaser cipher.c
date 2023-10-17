#include <stdio.h>
#include <ctype.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

int encrypt(int a, int b, int p) {
    return (a * p + b) % 26;
}

int decrypt(int a, int b, int c) {
    int aInverse = modInverse(a, 26);
    return (aInverse * (c - b + 26)) % 26;
}

int main() {
    int a, b, choice;
    char message[100];
    
    printf("Enter 'a' (a should be relatively prime to 26): ");
    scanf("%d", &a);
    printf("Enter 'b' (any integer): ");
    scanf("%d", &b);
    
    printf("Select an option:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter the plaintext: ");
        scanf(" %[^\n]", message);

        for (int i = 0; message[i] != '\0'; i++) {
            if (isalpha(message[i])) {
                char base = islower(message[i]) ? 'a' : 'A';
                int p = message[i] - base;
                int c = encrypt(a, b, p);
                message[i] = c + base;
            }
        }

        printf("Encrypted message: %s\n", message);
    } else if (choice == 2) {
        printf("Enter the ciphertext: ");
        scanf(" %[^\n]", message);

        for (int i = 0; message[i] != '\0'; i++) {
            if (isalpha(message[i])) {
                char base = islower(message[i]) ? 'a' : 'A';
                int c = message[i] - base;
                int p = decrypt(a, b, c);
                message[i] = p + base;
            }
        }

        printf("Decrypted message: %s\n", message);
    } else {
        printf("Invalid option.\n");
    }

    return 0;
}
