/*
 * Program 2: Monoalphabetic Substitution Cipher
 * Description: Maps each plaintext alphabet letter to a unique ciphertext alphabet letter.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Standard 26-letter substitution alphabet key
const char DEFAULT_KEY[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";

void mono_encrypt(const char *plain, char *cipher, const char *key) {
    int i = 0;
    for (; plain[i] != '\0'; i++) {
        if (isupper((unsigned char)plain[i])) {
            cipher[i] = key[plain[i] - 'A'];
        } else if (islower((unsigned char)plain[i])) {
            cipher[i] = (char)tolower((unsigned char)key[plain[i] - 'a']);
        } else {
            cipher[i] = plain[i];
        }
    }
    cipher[i] = '\0';
}

void mono_decrypt(const char *cipher, char *plain, const char *key) {
    int i = 0;
    for (; cipher[i] != '\0'; i++) {
        char c = cipher[i];
        if (isupper((unsigned char)c)) {
            for (int k = 0; k < 26; k++) {
                if (key[k] == c) {
                    plain[i] = (char)('A' + k);
                    break;
                }
            }
        } else if (islower((unsigned char)c)) {
            char upper_c = (char)toupper((unsigned char)c);
            for (int k = 0; k < 26; k++) {
                if (key[k] == upper_c) {
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
    char plain[256] = "ATTACKATDAWN";
    char cipher[256];
    char decrypted[256];

    printf("=========================================\n");
    printf(" EX 2: MONOALPHABETIC SUBSTITUTION CIPHER\n");
    printf("=========================================\n");
    printf("Substitution Key:\n");
    printf("Plain:  ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("Cipher: %s\n", DEFAULT_KEY);
    printf("-----------------------------------------\n");

    printf("Enter plaintext (press Enter for default '%s'): ", plain);
    char input[256];
    if (fgets(input, sizeof(input), stdin) && input[0] != '\n' && input[0] != '\r') {
        input[strcspn(input, "\r\n")] = '\0';
        strncpy(plain, input, sizeof(plain));
    } else {
        printf("\n[Using default plaintext: \"%s\"]\n", plain);
    }

    mono_encrypt(plain, cipher, DEFAULT_KEY);
    printf("\nPlaintext:      %s\n", plain);
    printf("Ciphertext:     %s\n", cipher);

    mono_decrypt(cipher, decrypted, DEFAULT_KEY);
    printf("Decrypted Text: %s\n", decrypted);
    printf("=========================================\n");

    return 0;
}
