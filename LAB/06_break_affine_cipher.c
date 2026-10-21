/*
 * Program 6: Cryptanalysis of Affine Cipher
 * Given:
 *  - Most frequent ciphertext letter is 'B'
 *  - Second most frequent ciphertext letter is 'U'
 * In English:
 *  - Most frequent plaintext letter is 'E' (index 4)
 *  - Second most frequent plaintext letter is 'T' (index 19)
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod_inverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main(void) {
    printf("=====================================================\n");
    printf("         EX 6: BREAKING AFFINE CIPHER                \n");
    printf("=====================================================\n");

    // English frequency assumptions:
    // 'E' -> index 4, 'T' -> index 19
    int p1 = 'E' - 'A'; // 4
    int p2 = 'T' - 'A'; // 19

    // Ciphertext frequencies:
    // 'B' -> index 1, 'U' -> index 20
    int c1 = 'B' - 'A'; // 1
    int c2 = 'U' - 'A'; // 20

    printf("Known mappings from Frequency Analysis:\n");
    printf("  'E' (p1 = %d) -> 'B' (c1 = %d)\n", p1, c1);
    printf("  'T' (p2 = %d) -> 'U' (c2 = %d)\n\n", p2, c2);

    printf("Equations:\n");
    printf("  (4 * a + b) = 1  (mod 26)  -- (1)\n");
    printf("  (19 * a + b) = 20 (mod 26)  -- (2)\n\n");

    // Subtract (1) from (2):
    // 15 * a = 19 (mod 26)
    int delta_p = (p2 - p1 + 26) % 26; // 15
    int delta_c = (c2 - c1 + 26) % 26; // 19

    int inv_delta_p = mod_inverse(delta_p, 26);
    printf("Subtracting (1) from (2):\n");
    printf("  %d * a = %d (mod 26)\n", delta_p, delta_c);
    printf("  Inverse of %d mod 26 = %d\n", delta_p, inv_delta_p);

    int a = (delta_c * inv_delta_p) % 26;
    int b = (c1 - a * p1) % 26;
    if (b < 0) b += 26;

    printf("\nCalculated Keys:\n");
    printf("  a = %d\n", a);
    printf("  b = %d\n", b);

    int a_inv = mod_inverse(a, 26);
    printf("  a_inverse = %d\n", a_inv);
    printf("Decryption formula: p = %d * (C - %d) mod 26\n\n", a_inv, b);

    // Demonstrate decryption of sample text
    char sample_cipher[] = "BU";
    printf("Verification on ciphertext \"%s\":\n", sample_cipher);
    for (int i = 0; sample_cipher[i] != '\0'; i++) {
        int c = sample_cipher[i] - 'A';
        int p = (a_inv * (c - b + 26 * 5)) % 26;
        printf("  Cipher '%c' -> Plain '%c'\n", sample_cipher[i], p + 'A');
    }
    printf("=====================================================\n");

    return 0;
}
