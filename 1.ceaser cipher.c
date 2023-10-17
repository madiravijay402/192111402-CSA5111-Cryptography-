#include <stdio.h>
#include <string.h>

void caesarCipher(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        if (ch >= 'A' && ch <= 'Z') {
            // For uppercase letters
            ch = ((ch - 'A' + shift) % 26) + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            // For lowercase letters
            ch = ((ch - 'a' + shift) % 26) + 'a';
        }

        printf("%c", ch);
    }
    printf("\n");
}

int main() {
    char text[100];
    printf("Enter a message: ");
    fgets(text, sizeof(text), stdin);
    
    for (int shift = 1; shift <= 25; shift++) {
        printf("Shift %d: ", shift);
        caesarCipher(text, shift);
    }

    return 0;
}
