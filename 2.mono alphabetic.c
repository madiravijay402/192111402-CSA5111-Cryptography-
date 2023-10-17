#include <stdio.h>
#include <string.h>
#include <ctype.h>

void createSubstitutionKey(char *key, char *substitutionKey) {
    for (int i = 0; i < 26; i++) {
        substitutionKey[i] = key[i];
    }
}

void encrypt(char *text, char *substitutionKey) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char ch = text[i];
            if (islower(ch)) {
                text[i] = substitutionKey[ch - 'a'];
            } else if (isupper(ch)) {
                text[i] = toupper(substitutionKey[ch - 'A']);
            }
        }
    }
}

int main() {
    char key[27] = "ZYXWVUTSRQPONMLKJIHGFEDCBA"; // Example substitution key
    char substitutionKey[26];

    createSubstitutionKey(key, substitutionKey);

    char text[100];
    printf("Enter a message: ");
    fgets(text, sizeof(text), stdin);

    encrypt(text, substitutionKey);

    printf("Encrypted message: %s\n", text);

    return 0;
}
