#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the cipher sequence based on the keyword
void generate_cipher_sequence(const char* keyword, char* cipher_sequence) {
    int used[26] = {0};
    int keyword_length = strlen(keyword);
    
    // Copy the keyword to the cipher sequence and mark the used characters
    for (int i = 0; i < keyword_length; i++) {
        char c = toupper(keyword[i]);
        if (isalpha(c) && !used[c - 'A']) {
            cipher_sequence[i] = c;
            used[c - 'A'] = 1;
        }
    }
    
    // Fill the remaining characters in normal order
    int j = 0;
    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            while (cipher_sequence[j] != 0)
                j++;
            cipher_sequence[j] = 'A' + i;
        }
    }
}

// Function to encrypt the plaintext
void monoalphabetic_encrypt(const char* plaintext, const char* keyword, char* ciphertext) {
    char cipher_sequence[26] = {0};
    generate_cipher_sequence(keyword, cipher_sequence);
    
    int length = strlen(plaintext);
    
    for (int i = 0; i < length; i++) {
        char c = toupper(plaintext[i]);
        if (isalpha(c)) {
            int index = c - 'A';
            if (islower(plaintext[i])) {
                ciphertext[i] = tolower(cipher_sequence[index]);
            } else {
                ciphertext[i] = cipher_sequence[index];
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
}

// Function to decrypt the ciphertext
void monoalphabetic_decrypt(const char* ciphertext, const char* keyword, char* decrypted_text) {
    char cipher_sequence[26] = {0};
    generate_cipher_sequence(keyword, cipher_sequence);
    
    int length = strlen(ciphertext);
    
    for (int i = 0; i < length; i++) {
        char c = toupper(ciphertext[i]);
        if (isalpha(c)) {
            int index = 0;
            while (cipher_sequence[index] != c) {
                index++;
            }
            if (islower(ciphertext[i])) {
                decrypted_text[i] = tolower('A' + index);
            } else {
                decrypted_text[i] = 'A' + index;
            }
        } else {
            decrypted_text[i] = ciphertext[i];
        }
    }
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "HELLO WORLD";
    char ciphertext[100] = {0};
    char decrypted_text[100] = {0};

    monoalphabetic_encrypt(plaintext, keyword, ciphertext);
    monoalphabetic_decrypt(ciphertext, keyword, decrypted_text);

    printf("Plaintext:  %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted:  %s\n", decrypted_text);

    return 0;
}
