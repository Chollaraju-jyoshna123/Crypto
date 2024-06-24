#include <stdio.h>
#include <stdbool.h>
#define ALPHABET_SIZE 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  
}
void decrypt(int ciphertext[2], int key[2][2], int plaintext[2]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0] + ALPHABET_SIZE) % ALPHABET_SIZE; 
    int detInverse = modInverse(det, ALPHABET_SIZE);  
    int adjKey[2][2];
    adjKey[0][0] = key[1][1];
    adjKey[0][1] = (ALPHABET_SIZE + (-key[0][1])) % ALPHABET_SIZE;
    adjKey[1][0] = (ALPHABET_SIZE + (-key[1][0])) % ALPHABET_SIZE;
    adjKey[1][1] = key[0][0];
    plaintext[0] = (detInverse * (adjKey[0][0] * ciphertext[0] + adjKey[0][1] * ciphertext[1])) % ALPHABET_SIZE;
    plaintext[1] = (detInverse * (adjKey[1][0] * ciphertext[0] + adjKey[1][1] * ciphertext[1])) % ALPHABET_SIZE;
    if (plaintext[0] < 0) {
        plaintext[0] += ALPHABET_SIZE;
    }
    if (plaintext[1] < 0) {
        plaintext[1] += ALPHABET_SIZE;
    }
}
int main() {
    int pairs[][4] = {
        {4, 4, 19, 4},  
        {4, 19, 19, 17}, 
        {19, 4, 17, 4}, 
        {19, 19, 17, 17}
    };
    int key[2][2];
    bool foundKey = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            for (int k = 0; k < ALPHABET_SIZE; k++) {
                for (int l = 0; l < ALPHABET_SIZE; l++) {
                    key[0][0] = i;
                    key[0][1] = j;
                    key[1][0] = k;
                    key[1][1] = l;
                    bool validKey = true;
                    for (int m = 0; m < 4; m++) {
                        int p1 = pairs[m][0];
                        int p2 = pairs[m][1];
                        int c1 = pairs[m][2];
                        int c2 = pairs[m][3];
                        int plaintext[2];
                        decrypt((int[]){c1, c2}, key, plaintext);
                        if (plaintext[0] != p1 || plaintext[1] != p2) {
                            validKey = false;
                            break;
                        }
                    }
                    if (validKey) {
                        foundKey = true;
                        printf("Found key matrix:\n");
                        printf("%d %d\n", key[0][0], key[0][1]);
                        printf("%d %d\n", key[1][0], key[1][1]);
                        break;
                    }
                }
                if (foundKey) break;
            }
            if (foundKey) break;
        }
        if (foundKey) break;
    }
    if (!foundKey) {
        printf("Key matrix not found.\n");
    }
    return 0;
}
