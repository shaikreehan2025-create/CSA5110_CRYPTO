/*
 * Program 4: Polyalphabetic Substitution Cipher (Vigenere Cipher)
 * Description: Uses repeated keyword to shift successive plaintext letters.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenere_encrypt(const char *plain, const char *key, char *cipher) {
    int key_len = strlen(key);
    int j = 0;
    int i = 0;
    for (; plain[i] != '\0'; i++) {
        if (isalpha((unsigned char)plain[i])) {
            char base = isupper((unsigned char)plain[i]) ? 'A' : 'a';
            char k_char = (char)toupper((unsigned char)key[j % key_len]) - 'A';
            cipher[i] = (char)(((plain[i] - base + k_char) % 26) + base);
            j++;
        } else {
            cipher[i] = plain[i];
        }
    }
    cipher[i] = '\0';
}

void vigenere_decrypt(const char *cipher, const char *key, char *plain) {
    int key_len = strlen(key);
    int j = 0;
    int i = 0;
    for (; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i])) {
            char base = isupper((unsigned char)cipher[i]) ? 'A' : 'a';
            char k_char = (char)toupper((unsigned char)key[j % key_len]) - 'A';
            plain[i] = (char)(((cipher[i] - base - k_char + 26) % 26) + base);
            j++;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[i] = '\0';
}

int main(void) {
    char plain[256] = "GEEKSFORGEEKS";
    char key[64] = "AYUSH";
    char cipher[256];
    char decrypted[256];

    printf("=========================================\n");
    printf("   EX 4: POLYALPHABETIC (VIGENERE) CIPHER\n");
    printf("=========================================\n");

    printf("Enter plaintext (press Enter for default '%s'): ", plain);
    char input[256];
    if (fgets(input, sizeof(input), stdin) && input[0] != '\n' && input[0] != '\r') {
        input[strcspn(input, "\r\n")] = '\0';
        strncpy(plain, input, sizeof(plain));
    }

    printf("Enter key (press Enter for default '%s'): ", key);
    if (fgets(input, sizeof(input), stdin) && input[0] != '\n' && input[0] != '\r') {
        input[strcspn(input, "\r\n")] = '\0';
        strncpy(key, input, sizeof(key));
    }

    vigenere_encrypt(plain, key, cipher);
    printf("\nPlaintext:      %s\n", plain);
    printf("Key:            %s\n", key);
    printf("Ciphertext:     %s\n", cipher);

    vigenere_decrypt(cipher, key, decrypted);
    printf("Decrypted Text: %s\n", decrypted);
    printf("=========================================\n");

    return 0;
}
