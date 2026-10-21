/*
 * Program 9: Decryption of Historic PT-109 Playfair Message
 * Description: Decrypts message received at Australian wireless station regarding PT-109.
 * Secret Key used by coastwatcher: "ROYAL NEW ZEALAND NAVY"
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void build_matrix(const char *key) {
    int used[26] = {0};
    used['J' - 'A'] = 1;
    int row = 0, col = 0;

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
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            matrix[row][col++] = c;
            used[c - 'A'] = 1;
            if (col == 5) { col = 0; row++; }
        }
    }
}

void find_pos(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

void decrypt_playfair(const char *cipher, char *plain) {
    int len = strlen(cipher);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        find_pos(cipher[i], &r1, &c1);
        find_pos(cipher[i + 1], &r2, &c2);

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
    const char *key = "ROYAL NEW ZEALAND NAVY";
    const char *raw_cipher = 
        "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY "
        "CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";

    char clean_cipher[512];
    int len = 0;
    for (int i = 0; raw_cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)raw_cipher[i])) {
            clean_cipher[len++] = (char)toupper((unsigned char)raw_cipher[i]);
        }
    }
    clean_cipher[len] = '\0';

    build_matrix(key);

    printf("=====================================================\n");
    printf("         EX 9: PT-109 PLAYFAIR CODE DECRYPTION       \n");
    printf("=====================================================\n");
    printf("Key: %s\n\nPlayfair Matrix:\n", key);
    for (int r = 0; r < 5; r++) {
        printf("  ");
        for (int c = 0; c < 5; c++) printf("%c ", matrix[r][c]);
        printf("\n");
    }
    printf("\nRaw Ciphertext:\n%s\n\n", raw_cipher);

    char decrypted[512];
    decrypt_playfair(clean_cipher, decrypted);

    printf("Decrypted Raw Text:\n%s\n\n", decrypted);
    printf("Interpreted Historical Plaintext:\n");
    printf("\"PT ONE O NINE LOST IN ACTION IN BLACKETT STRAIT\n"
           " TWO MILES SW MERESU COVE X CREW OF TWELVE REQUEST\n"
           " ANY AVAILABLE AIR RESCUE\"\n");
    printf("=====================================================\n");

    return 0;
}
