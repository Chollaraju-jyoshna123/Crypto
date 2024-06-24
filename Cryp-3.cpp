#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5 
void prepareKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]) {
    int i, j, k;
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; 
    int len = strlen(key);
    int len_alphabet = strlen(alphabet);
    for (i = 0, k = 0; i < len; ++i) {
        if (!isalpha(key[i])) continue;
        key[i] = toupper(key[i]);
        for (j = 0; j < len_alphabet; ++j) {
            if (key[i] == alphabet[j]) {
                alphabet[j] = '0';
                keyMatrix[k / SIZE][k % SIZE] = key[i];
                ++k;
                break;
            }
        }
    }
    for (i = 0; i < len_alphabet; ++i) {
        if (alphabet[i] != '0') {
            keyMatrix[k / SIZE][k % SIZE] = alphabet[i];
            ++k;
        }
    }
}
void findPosition(char keyMatrix[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptMessage(char message[], char keyMatrix[SIZE][SIZE]) {
    int i, len = strlen(message);
    char a, b;
    int r1, r2, c1, c2;
    for (i = 0; i < len; i += 2) {
        if (message[i] == message[i + 1]) {
            memmove(&message[i + 1], &message[i], strlen(&message[i]) + 1);
            message[i + 1] = 'X';
            ++len;
        }
    }
    for (i = 0; i < len; i += 2) {
        a = message[i];
        b = message[i + 1];
        findPosition(keyMatrix, a, &r1, &c1);
        if (r1 == r2) {
            message[i] = keyMatrix[r1][(c1 + 1) % SIZE];
            message[i + 1] = keyMatrix[r2][(c2 + 1) % SIZE];
        }
        else if (c1 == c2) {
            message[i] = keyMatrix[(r1 + 1) % SIZE][c1];
            message[i + 1] = keyMatrix[(r2 + 1) % SIZE][c2];
        }
        else {
            message[i] = keyMatrix[r1][c2];
            message[i + 1] = keyMatrix[r2][c1];
        }
    }
}
int main() {
    char key[100], message[100];
    char keyMatrix[SIZE][SIZE];
    int i, j;
    printf("Enter the key for Playfair cipher (no 'J' and all uppercase letters): ");
    fgets(key, sizeof(key), stdin);
    key[strlen(key) - 1] = '\0'; 
    prepareKeyMatrix(key, keyMatrix);
    printf("Enter the message to encrypt (uppercase letters only): ");
    fgets(message, sizeof(message), stdin);
    message[strlen(message) - 1] = '\0'; 
    encryptMessage(message, keyMatrix);
    printf("Encrypted message: %s\n", message);
    return 0;
}
