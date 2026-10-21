/*
 * Program 10: Playfair Cipher with Predefined Matrix
 * Matrix provided:
 *   M F H I/J K
 *   U N O P   Q
 *   Z V W X   Y
 *   E L A R   G
 *   D S T B   C
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char MATRIX[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void find_pos(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (MATRIX[i][j] == ch) {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

int format_input(const char *in, char *out) {
    int len = 0;
    for (int i = 0; in[i] != '\0'; i++) {
        if (isalpha((unsigned char)in[i])) {
            char c = (char)toupper((unsigned char)in[i]);
            if (c == 'J') c = 'I';
            out[len++] = c;
        }
    }
    out[len] = '\0';

    char formatted[512];
    int flen = 0;
    for (int i = 0; i < len; i++) {
        formatted[flen++] = out[i];
        if (i + 1 < len) {
            if (out[i] == out[i + 1]) {
                formatted[flen++] = 'X';
            } else {
                formatted[flen++] = out[++i];
            }
        }
    }
    if (flen % 2 != 0) formatted[flen++] = 'X';
    formatted[flen] = '\0';
    strcpy(out, formatted);
    return flen;
}

void encrypt_playfair(const char *plain, char *cipher) {
    int len = strlen(plain);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        find_pos(plain[i], &r1, &c1);
        find_pos(plain[i + 1], &r2, &c2);

        if (r1 == r2) {
            cipher[i]     = MATRIX[r1][(c1 + 1) % 5];
            cipher[i + 1] = MATRIX[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            cipher[i]     = MATRIX[(r1 + 1) % 5][c1];
            cipher[i + 1] = MATRIX[(r2 + 1) % 5][c2];
        } else {
            cipher[i]     = MATRIX[r1][c2];
            cipher[i + 1] = MATRIX[r2][c1];
        }
    }
    cipher[len] = '\0';
}

void decrypt_playfair(const char *cipher, char *plain) {
    int len = strlen(cipher);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        find_pos(cipher[i], &r1, &c1);
        find_pos(cipher[i + 1], &r2, &c2);

        if (r1 == r2) {
            plain[i]     = MATRIX[r1][(c1 + 4) % 5];
            plain[i + 1] = MATRIX[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            plain[i]     = MATRIX[(r1 + 4) % 5][c1];
            plain[i + 1] = MATRIX[(r2 + 4) % 5][c2];
        } else {
            plain[i]     = MATRIX[r1][c2];
            plain[i + 1] = MATRIX[r2][c1];
        }
    }
    plain[len] = '\0';
}

int main(void) {
    char plain[256] = "HELLOWORLD";
    char formatted[512], cipher[512], decrypted[512];

    printf("=====================================================\n");
    printf("   EX 10: PLAYFAIR CIPHER (CUSTOM MATRIX)            \n");
    printf("=====================================================\n");
    printf("Predefined 5x5 Matrix:\n");
    for (int r = 0; r < 5; r++) {
        printf("  ");
        for (int c = 0; c < 5; c++) {
            if (MATRIX[r][c] == 'I') printf("I/J ");
            else printf("%c   ", MATRIX[r][c]);
        }
        printf("\n");
    }
    printf("-----------------------------------------------------\n");

    printf("Enter plaintext (press Enter for default '%s'): ", plain);
    char input[256];
    if (fgets(input, sizeof(input), stdin) && input[0] != '\n' && input[0] != '\r') {
        input[strcspn(input, "\r\n")] = '\0';
        strncpy(plain, input, sizeof(plain));
    }

    format_input(plain, formatted);
    printf("\nProcessed Digraph Plaintext: %s\n", formatted);

    encrypt_playfair(formatted, cipher);
    printf("Ciphertext:                  %s\n", cipher);

    decrypt_playfair(cipher, decrypted);
    printf("Decrypted Plaintext:         %s\n", decrypted);
    printf("=====================================================\n");

    return 0;
}
