/*
 * Program 5: Generalization of Caesar Cipher (Affine Cipher)
 * Form: C = (a * p + b) mod 26
 *
 * Theory & Questions Answered:
 * a. Are there any limitations on the value of b?
 *    Answer: No coprimality limitations on b. b can be any integer from 0 to 25.
 *            It simply acts as an additive shift.
 *
 * b. Determine which values of a are not allowed:
 *    Answer: For the cipher to be one-to-one (injective), gcd(a, 26) must be 1.
 *            Therefore, values sharing a factor (2 or 13) with 26 are NOT allowed:
 *            Even values: 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24
 *            Multiple of 13: 13
 *            Total invalid values = 14.
 *            Allowed values of a are {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25} (12 values).
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

void affine_encrypt(const char *plain, char *cipher, int a, int b) {
    int i = 0;
    for (; plain[i] != '\0'; i++) {
        if (isupper((unsigned char)plain[i])) {
            int p = plain[i] - 'A';
            cipher[i] = (char)(((a * p + b) % 26) + 'A');
        } else if (islower((unsigned char)plain[i])) {
            int p = plain[i] - 'a';
            cipher[i] = (char)(((a * p + b) % 26) + 'a');
        } else {
            cipher[i] = plain[i];
        }
    }
    cipher[i] = '\0';
}

void affine_decrypt(const char *cipher, char *plain, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    int i = 0;
    for (; cipher[i] != '\0'; i++) {
        if (isupper((unsigned char)cipher[i])) {
            int c = cipher[i] - 'A';
            int p = (a_inv * (c - b + 26 * 2)) % 26;
            plain[i] = (char)(p + 'A');
        } else if (islower((unsigned char)cipher[i])) {
            int c = cipher[i] - 'a';
            int p = (a_inv * (c - b + 26 * 2)) % 26;
            plain[i] = (char)(p + 'a');
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[i] = '\0';
}

int main(void) {
    int a = 7, b = 2;
    char text[256] = "AFFINECIPHER";
    char cipher[256], decrypted[256];

    printf("=====================================================\n");
    printf("       EX 5: AFFINE CIPHER & KEY SPACE ANALYSIS      \n");
    printf("=====================================================\n");
    printf("Formula: C = (a * p + b) mod 26\n\n");
    printf("--- Theoretical Analysis ---\n");
    printf("a. Limitations on b: b in [0, 25]. Any integer shift is valid.\n");
    printf("b. Disallowed values of 'a' (must have gcd(a, 26) == 1):\n");
    printf("   Not allowed: ");
    for (int i = 0; i < 26; i++) {
        if (gcd(i, 26) != 1) printf("%d ", i);
    }
    printf("\n   Allowed:     ");
    for (int i = 0; i < 26; i++) {
        if (gcd(i, 26) == 1) printf("%d ", i);
    }
    printf("\n-----------------------------------------------------\n");

    printf("Selected Key: a = %d, b = %d (gcd(%d, 26) = %d)\n", a, b, a, gcd(a, 26));
    printf("Plaintext:    %s\n", text);

    affine_encrypt(text, cipher, a, b);
    printf("Ciphertext:   %s\n", cipher);

    affine_decrypt(cipher, decrypted, a, b);
    printf("Decrypted:    %s\n", decrypted);
    printf("=====================================================\n");

    return 0;
}
