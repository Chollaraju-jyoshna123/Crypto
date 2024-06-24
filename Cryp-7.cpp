#include <stdio.h>
#include <string.h>
#include <ctype.h>
void decryptSubstitutionCipher(char ciphertext[]) {
    float freq[26] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094,
                      6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929,
                      0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
                      1.974, 0.074};
    int count[256] = {0};
    int i, maxCount = 0, maxIndex = 0;
    int len = strlen(ciphertext);
    for (i = 0; i < len; ++i) {
        count[ciphertext[i]]++;
    }
    for (i = 0; i < 256; ++i) {
        if (isalpha(i) && count[i] > maxCount) {
            maxCount = count[i];
            maxIndex = i;
        }
    }
    int shift = maxIndex - 'e';
    for (i = 0; i < len; ++i) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            ciphertext[i] = ((ciphertext[i] - base - shift + 26) % 26) + base;
        }
    }
}
int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                        "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
                        ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 "
                        "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    decryptSubstitutionCipher(ciphertext);
    printf("Decrypted message: %s\n", ciphertext);
    return 0;
}
