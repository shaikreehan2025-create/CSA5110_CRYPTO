/*
 * Program 8: Monoalphabetic Cipher with Keyword-Generated Alphabet
 * Description: Uses keyword (e.g., "CIPHER") to build substitution alphabet.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void build_cipher_alphabet(const char *keyword, char *cipher_alpha) {
    int used[26] = {0};
    int idx = 0;

    // Insert unique characters of keyword
    for (int i = 0; keyword[i] != '\0'; i++) {
        if (isalpha((unsigned char)keyword[i])) {
            char c = (char)toupper((unsigned char)keyword[i]);
            if (!used[c - 'A']) {
                cipher_alpha[idx++] = c;
                used[c - 'A'] = 1;
            }
        }
    }

    // Append remaining letters of alphabet
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            cipher_alpha[idx++] = c;
            used[c - 'A'] = 1;
        }
    }
    cipher_alpha[26] = '\0';
}

void encrypt(const char *plain, const char *cipher_alpha, char *cipher) {
    int i = 0;
    for (; plain[i] != '\0'; i++) {
        if (isupper((unsigned char)plain[i])) {
            cipher[i] = cipher_alpha[plain[i] - 'A'];
        } else if (islower((unsigned char)plain[i])) {
            cipher[i] = (char)tolower((unsigned char)cipher_alpha[plain[i] - 'a']);
        } else {
            cipher[i] = plain[i];
        }
    }
    cipher[i] = '\0';
}

void decrypt(const char *cipher, const char *cipher_alpha, char *plain) {
    int i = 0;
    for (; cipher[i] != '\0'; i++) {
        char c = cipher[i];
        if (isupper((unsigned char)c)) {
            for (int k = 0; k < 26; k++) {
                if (cipher_alpha[k] == c) {
                    plain[i] = (char)('A' + k);
                    break;
                }
            }
        } else if (islower((unsigned char)c)) {
            char upper_c = (char)toupper((unsigned char)c);
            for (int k = 0; k < 26; k++) {
                if (cipher_alpha[k] == upper_c) {
                    plain[i] = (char)('a' + k);
                    break;
                }
            }
        } else {
            plain[i] = c;
        }
    }
    plain[i] = '\0';
}

int main(void) {
    char keyword[64] = "CIPHER";
    char cipher_alpha[27];
    char plain[256] = "attack at dawn";
    char cipher[256], decrypted[256];

    printf("=====================================================\n");
    printf("   EX 8: KEYWORD-GENERATED MONOALPHABETIC CIPHER     \n");
    printf("=====================================================\n");

    printf("Enter keyword (press Enter for default '%s'): ", keyword);
    char input[128];
    if (fgets(input, sizeof(input), stdin) && input[0] != '\n' && input[0] != '\r') {
        input[strcspn(input, "\r\n")] = '\0';
        strncpy(keyword, input, sizeof(keyword));
    }

    build_cipher_alphabet(keyword, cipher_alpha);

    printf("\nAlphabet Mapping:\n");
    printf("Plain:  abcdefghijklmnopqrstuvwxyz\n");
    printf("Cipher: %s\n", cipher_alpha);
    printf("-----------------------------------------------------\n");

    encrypt(plain, cipher_alpha, cipher);
    printf("Plaintext:  %s\n", plain);
    printf("Ciphertext: %s\n", cipher);

    decrypt(cipher, cipher_alpha, decrypted);
    printf("Decrypted:  %s\n", decrypted);
    printf("=====================================================\n");

    return 0;
}
