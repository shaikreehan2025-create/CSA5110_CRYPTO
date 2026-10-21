/*
 * Program 3: Playfair Cipher Algorithm
 * Description: 5x5 matrix construction from keyword, 2-letter digraph encryption and decryption.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void generate_matrix(const char *key) {
    int used[26] = {0};
    used['J' - 'A'] = 1; // 'I' and 'J' share the same cell
    int row = 0, col = 0;

    // Process key
    for (int i = 0; key[i] != '\0'; i++) {
        if (!isalpha((unsigned char)key[i])) continue;
        char c = (char)toupper((unsigned char)key[i]);
        if (c == 'J') c = 'I';
        if (!used[c - 'A']) {
            matrix[row][col++] = c;
            used[c - 'A'] = 1;
            if (col == 5) { col = 0; row++; }
        }
    }

    // Process remaining alphabet
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            matrix[row][col++] = c;
            used[c - 'A'] = 1;
            if (col == 5) { col = 0; row++; }
        }
    }
}

void print_matrix(void) {
    printf("Playfair 5x5 Matrix:\n");
    for (int r = 0; r < 5; r++) {
        printf("  ");
        for (int c = 0; c < 5; c++) {
            printf("%c ", matrix[r][c]);
        }
        printf("\n");
    }
}

void find_position(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (matrix[r][c] == ch) {
                *row = r;
                *col = c;
                return;
            }
        }
    }
}

int format_plaintext(const char *in, char *out) {
    int len = 0;
    for (int i = 0; in[i] != '\0'; i++) {
        if (isalpha((unsigned char)in[i])) {
            char c = (char)toupper((unsigned char)in[i]);
            if (c == 'J') c = 'I';
            out[len++] = c;
        }
    }
    out[len] = '\0';

    // Insert 'X' between duplicate adjacent letters in same pair
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
    // Pad odd length with 'X'
    if (flen % 2 != 0) {
        formatted[flen++] = 'X';
    }
    formatted[flen] = '\0';
    strcpy(out, formatted);
    return flen;
}

void playfair_encrypt(const char *plain, char *cipher) {
    int len = strlen(plain);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        find_position(plain[i], &r1, &c1);
        find_position(plain[i + 1], &r2, &c2);

        if (r1 == r2) {
            cipher[i]     = matrix[r1][(c1 + 1) % 5];
            cipher[i + 1] = matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            cipher[i]     = matrix[(r1 + 1) % 5][c1];
            cipher[i + 1] = matrix[(r2 + 1) % 5][c2];
        } else {
            cipher[i]     = matrix[r1][c2];
            cipher[i + 1] = matrix[r2][c1];
        }
    }
    cipher[len] = '\0';
}

void playfair_decrypt(const char *cipher, char *plain) {
    int len = strlen(cipher);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        find_position(cipher[i], &r1, &c1);
        find_position(cipher[i + 1], &r2, &c2);

        if (r1 == r2) {
            plain[i]     = matrix[r1][(c1 + 4) % 5];
            plain[i + 1] = matrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            plain[i]     = matrix[(r1 + 4) % 5][c1];
            plain[i + 1] = matrix[(r2 + 4) % 5][c2];
        } else {
            plain[i]     = matrix[r1][c2];
            plain[i + 1] = matrix[r2][c1];
        }
    }
    plain[len] = '\0';
}

int main(void) {
    char key[64] = "MONARCHY";
    char plaintext[256] = "INSTRUMENTS";
    char processed[512], cipher[512], decrypted[512];

    printf("=========================================\n");
    printf("         EX 3: PLAYFAIR CIPHER           \n");
    printf("=========================================\n");

    printf("Enter keyword (press Enter for default '%s'): ", key);
    char input[128];
    if (fgets(input, sizeof(input), stdin) && input[0] != '\n' && input[0] != '\r') {
        input[strcspn(input, "\r\n")] = '\0';
        strncpy(key, input, sizeof(key));
    }

    generate_matrix(key);
    print_matrix();
    printf("-----------------------------------------\n");

    printf("Enter plaintext (press Enter for default '%s'): ", plaintext);
    if (fgets(input, sizeof(input), stdin) && input[0] != '\n' && input[0] != '\r') {
        input[strcspn(input, "\r\n")] = '\0';
        strncpy(plaintext, input, sizeof(plaintext));
    }

    format_plaintext(plaintext, processed);
    printf("\nProcessed Plaintext (Digraphs): %s\n", processed);

    playfair_encrypt(processed, cipher);
    printf("Ciphertext:                    %s\n", cipher);

    playfair_decrypt(cipher, decrypted);
    printf("Decrypted Plaintext:           %s\n", decrypted);
    printf("=========================================\n");

    return 0;
}
