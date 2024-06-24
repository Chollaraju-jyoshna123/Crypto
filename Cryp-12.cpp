#include <stdio.h>
#include <string.h>
#include <ctype.h>
int charToNum(char c) {
    return tolower(c) - 'a';
}
char numToChar(int num) {
    return num + 'a';
}
void encrypt(char *plaintext, char *ciphertext, int key[2][2]) {
    int len = strlen(plaintext);
    int i, j;
    for (i = 0; i < len; i += 2) {
        int p1 = charToNum(plaintext[i]);
        int p2 = (i + 1 < len) ? charToNum(plaintext[i + 1]) : charToNum('x'); 
        int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;
        ciphertext[i] = numToChar(c1);
        if (i + 1 < len) {
            ciphertext[i + 1] = numToChar(c2);
        }
    }
    ciphertext[len] = '\0'; 
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  
}
void decrypt(char *ciphertext, char *decryptedtext, int key[2][2]) {
    int len = strlen(ciphertext);
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0] + 26) % 26;  
    int detInverse = modInverse(det, 26);  
    int adjKey[2][2];
    adjKey[0][0] = key[1][1];
    adjKey[0][1] = (26 + (-key[0][1])) % 26;
    adjKey[1][0] = (26 + (-key[1][0])) % 26;
    adjKey[1][1] = key[0][0];
    for (int i = 0; i < len; i += 2) {
        int c1 = charToNum(ciphertext[i]);
        int c2 = (i + 1 < len) ? charToNum(ciphertext[i + 1]) : charToNum('x');  
        int p1 = (detInverse * (adjKey[0][0] * c1 + adjKey[0][1] * c2)) % 26;
        int p2 = (detInverse * (adjKey[1][0] * c1 + adjKey[1][1] * c2)) % 26;
        decryptedtext[i] = numToChar(p1);
        if (i + 1 < len) {
            decryptedtext[i + 1] = numToChar(p2);
        }
    }
    decryptedtext[len] = '\0'; 
}
int main() {
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    char ciphertext[100];  
    encrypt(plaintext, ciphertext, key);
    printf("Encrypted ciphertext: %s\n", ciphertext);
    char decryptedtext[100]; 
    decrypt(ciphertext, decryptedtext, key);
    printf("Decrypted plaintext: %s\n", decryptedtext);   
    return 0;
}
