/*
 * Program 1: Caesar Cipher Implementation
 * Description: Replaces each letter of the alphabet with the letter standing k places further down (1 <= k <= 25).
 * Suitable for all standard online C compilers.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesar_encrypt(char *text, int k) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper((unsigned char)text[i])) {
            text[i] = (char)(((text[i] - 'A' + k) % 26) + 'A');
        } else if (islower((unsigned char)text[i])) {
            text[i] = (char)(((text[i] - 'a' + k) % 26) + 'a');
        }
    }
}

void caesar_decrypt(char *text, int k) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper((unsigned char)text[i])) {
            text[i] = (char)(((text[i] - 'A' - k + 26) % 26) + 'A');
        } else if (islower((unsigned char)text[i])) {
            text[i] = (char)(((text[i] - 'a' - k + 26) % 26) + 'a');
        }
    }
}

int main(void) {
    char text[256] = "HELLOWORLD";
    int k = 3;

    printf("=========================================\n");
    printf("   EX 1: CAESAR CIPHER (SHIFT CIPHER)    \n");
    printf("=========================================\n");

    printf("Enter plaintext (or press Enter for default '%s'): ", text);
    char input[256];
    if (fgets(input, sizeof(input), stdin) && input[0] != '\n' && input[0] != '\r') {
        input[strcspn(input, "\r\n")] = '\0';
        strncpy(text, input, sizeof(text));
        printf("Enter shift key k (1-25): ");
        if (scanf("%d", &k) != 1 || k < 1 || k > 25) {
            printf("Invalid key! Defaulting to 3.\n");
            k = 3;
        }
    } else {
        printf("\n[Using default plaintext: \"%s\", key: %d]\n", text, k);
    }

    printf("\nOriginal Plaintext: %s\n", text);
    printf("Shift Key (k):      %d\n", k);

    caesar_encrypt(text, k);
    printf("Ciphertext:         %s\n", text);

    caesar_decrypt(text, k);
    printf("Decrypted Text:     %s\n", text);
    printf("=========================================\n");

    return 0;
}
