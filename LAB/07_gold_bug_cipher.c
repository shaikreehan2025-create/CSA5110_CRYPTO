/*
 * Program 7: Edgar Allan Poe's "The Gold-Bug" Substitution Cipher Decryption
 * Description: Frequency analysis and deductive decryption of Poe's cipher.
 */

#include <stdio.h>
#include <string.h>

// Full ciphertext from Edgar Allan Poe's "The Gold-Bug"
const char *CIPHERTEXT = 
    "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
    " (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
    " ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
    " (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";

// Decodes a UTF-8 character or multi-byte sequence to English plaintext letter
char decode_symbol(const char **ptr) {
    unsigned char c = (unsigned char)**ptr;
    
    // Check for UTF-8 multi-byte characters
    if (c == 0xE2 && (unsigned char)(*ptr)[1] == 0x80 && (unsigned char)(*ptr)[2] == 0xA1) {
        // ‡ (Double dagger: U+2021) -> 'o'
        *ptr += 3;
        return 'o';
    } else if (c == 0xE2 && (unsigned char)(*ptr)[1] == 0x80 && (unsigned char)(*ptr)[2] == 0xA0) {
        // † (Dagger: U+2020) -> 'd'
        *ptr += 3;
        return 'd';
    } else if (c == 0xC2 && (unsigned char)(*ptr)[1] == 0xB6) {
        // ¶ (Pilcrow: U+00B6) -> 'v'
        *ptr += 2;
        return 'v';
    } else if (c == 0xE2 && (unsigned char)(*ptr)[1] == 0x80 && (unsigned char)(*ptr)[2] == 0x94) {
        // — (Em-dash: U+2014) -> 'c'
        *ptr += 3;
        return 'c';
    }

    // Standard ASCII symbols
    (*ptr)++;
    switch (c) {
        case '5': return 'a';
        case '2': return 'b';
        case '-': return 'c';
        case '8': return 'e';
        case '1': return 'f';
        case '3': return 'g';
        case '4': return 'h';
        case '6': return 'i';
        case '0': return 'l';
        case '9': return 'm';
        case '*': return 'n';
        case '.': return 'p';
        case '(': return 'r';
        case ')': return 's';
        case ';': return 't';
        case '?': return 'u';
        case ']': return 'w';
        case ':': return 'y';
        case ' ': return ' ';
        case '\n': return '\n';
        default:  return (char)c;
    }
}

int main(void) {
    printf("=====================================================\n");
    printf("   EX 7: POE'S 'THE GOLD-BUG' SUBSTITUTION CIPHER    \n");
    printf("=====================================================\n");

    printf("Analysis Walkthrough:\n");
    printf("1. '8' is the most frequent character (33 times) -> 'e'.\n");
    printf("2. ';48' is the most frequent 3-character group -> 'the'\n");
    printf("   Therefore: ';' = 't', '4' = 'h', '8' = 'e'.\n");
    printf("3. ';48(88' translates to 'the(ee' -> '(' = 'r' (forming 'there' / 'the tree').\n");
    printf("4. '53‡‡†' at the start translates to 'a g o o d' -> '5'='a', '3'='g', '‡'='o', '†'='d'.\n");
    printf("5. Completing deductions for remaining characters:\n");
    printf("   0:l, 1:f, 2:b, -/—:c, 6:i, 9:m, *:n, .:p, ):s, ?:u, ¶:v, ]:w, ::y\n\n");

    printf("Decrypted Plaintext Message:\n\n");
    const char *p = CIPHERTEXT;
    while (*p != '\0') {
        putchar(decode_symbol(&p));
    }
    printf("\n\n-----------------------------------------------------\n");
    printf("Formatted Message:\n");
    printf("\"A good glass in the bishop's hostel in the devil's seat\n"
           " forty-one degrees and thirteen minutes northeast and by north\n"
           " main branch seventh limb east side shoot from the left eye\n"
           " of the death's-head a bee line from the tree through the shot\n"
           " fifty feet out.\"\n");
    printf("=====================================================\n");

    return 0;
}
