#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

// Padding function to add PKCS7 padding
int addPKCS7Padding(unsigned char* data, int data_len, int block_size) {
    int padding = block_size - (data_len % block_size);
    for (int i = 0; i < padding; i++) {
        data[data_len + i] = padding;
    }
    return data_len + padding;
}

int main() {
    // Initialize AES context and key
    AES_KEY aesKey;
    unsigned char key[16] = "AES128Encryption";
    unsigned char iv[16] = "InitializationIV";
    unsigned char plaintext[64] = "This is a sample message.";
    unsigned char ciphertext[64];
    unsigned char decrypted[64];

    int plaintext_len = strlen((const char*)plaintext);
    int block_size = 16;  // AES block size is 16 bytes

    // Add PKCS7 padding
    plaintext_len = addPKCS7Padding(plaintext, plaintext_len, block_size);

    // ECB mode encryption
    AES_set_encrypt_key(key, 128, &aesKey);
    AES_ecb_encrypt(plaintext, ciphertext, &aesKey, AES_ENCRYPT);

    // CBC mode encryption
    AES_set_encrypt_key(key, 128, &aesKey);
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &aesKey, iv, AES_ENCRYPT);

    // CFB mode encryption
    AES_set_encrypt_key(key, 128, &aesKey);
    AES_cfb128_encrypt(plaintext, ciphertext, plaintext_len, &aesKey, iv, NULL, AES_ENCRYPT);

    // Decrypt and remove PKCS7 padding
    AES_set_decrypt_key(key, 128, &aesKey);
    AES_ecb_encrypt(ciphertext, decrypted, &aesKey, AES_DECRYPT);

    printf("ECB Decrypted: %s\n", (char*)decrypted);

    AES_cbc_encrypt(ciphertext, decrypted, plaintext_len, &aesKey, iv, AES_DECRYPT);
    printf("CBC Decrypted: %s\n", (char*)decrypted);

    AES_cfb128_encrypt(ciphertext, decrypted, plaintext_len, &aesKey, iv, NULL, AES_DECRYPT);
    printf("CFB Decrypted: %s\n", (char*)decrypted);

    return 0;
}
