#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; 
}
void countFrequencies(char ciphertext[], int freq[]) {
    int i;
    int len = strlen(ciphertext);
    for (i = 0; i < len; ++i) {
        if (isalpha(ciphertext[i])) {
            char ch = tolower(ciphertext[i]);
            freq[ch - 'a']++;
        }
    }
}
void findAffineKey(char ciphertext[], int *a, int *b) {
    int freq[ALPHABET_SIZE] = {0};
    countFrequencies(ciphertext, freq);
    int maxFreqIndex = 0;
    for (int i = 1; i < ALPHABET_SIZE; ++i) {
        if (freq[i] > freq[maxFreqIndex]) {
            maxFreqIndex = i;
        }
    }
    int eIndex = 'e' - 'a';
    int tIndex = 't' - 'a';
    *b = (eIndex - maxFreqIndex + ALPHABET_SIZE) % ALPHABET_SIZE; 
    int diff = (tIndex - eIndex + ALPHABET_SIZE) % ALPHABET_SIZE;
    for (int i = 1; i < ALPHABET_SIZE; ++i) {
        if ((diff * i) % ALPHABET_SIZE == 1) {
            *a = i;
            break;
        }
    }
}
void affineCipherDecrypt(char ciphertext[], int a, int b) {
    int i;
    int len = strlen(ciphertext);
    for (i = 0; i < len; ++i) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            int c = tolower(ciphertext[i]) - 'a';
            int p = ((modInverse(a, ALPHABET_SIZE) * (c - b + ALPHABET_SIZE)) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
            ciphertext[i] = base + p;
        }
    }
}
int main() {
    char ciphertext[100];
    int a, b;
    printf("Enter the ciphertext (uppercase/lowercase letters only): ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 
    findAffineKey(ciphertext, &a, &b);
    affineCipherDecrypt(ciphertext, a, b);
    printf("Decrypted message: %s\n", ciphertext);
    return 0;
}
