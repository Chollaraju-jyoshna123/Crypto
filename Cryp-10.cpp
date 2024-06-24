#include <stdio.h>
#include <string.h>
#include <ctype.h>
void preparePlainText(char plaintext[]) {
    int i, j = 0;
    int len = strlen(plaintext);
    for (i = 0; i < len; ++i) {
        plaintext[i] = toupper(plaintext[i]);
    }
    for (i = 0; i < len; ++i) {
        if (isalpha(plaintext[i])) {
            if (plaintext[i] == 'J') {
                plaintext[j++] = 'I';
            } else {
                plaintext[j++] = plaintext[i];
            }
        }
    }
    plaintext[j] = '\0';
    for (i = 0; i < j; i += 2) {
        if (plaintext[i] == plaintext[i + 1]) {
            memmove(&plaintext[i + 1], &plaintext[i], strlen(plaintext) - i + 1);
            plaintext[i + 1] = 'X';
            j++;
        }
    }
    if (j % 2 != 0) {
        plaintext[j++] = 'X';
        plaintext[j] = '\0';
    }
}
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; 
    for (*row = 0; *row < 5; ++(*row)) {
        for (*col = 0; *col < 5; ++(*col)) {
            if (matrix[*row][*col] == ch) {
                return;
            }
        }
    }
}
void encryptPlayfair(char plaintext[], char matrix[5][5], char ciphertext[]) {
    int i;
    int len = strlen(plaintext);
    int row1, col1, row2, col2;
    for (i = 0; i < len; i += 2) {
        findPosition(matrix, plaintext[i], &row1, &col1);
        findPosition(matrix, plaintext[i + 1], &row2, &col2);
        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % 5];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % 5];
        }
        else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % 5][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % 5][col2];
        }
        else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}
int main() {
    char plaintext[] = "Must see you over Cadogan West. Coming at once";
    char matrix[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };
    char ciphertext[100] = "";
    preparePlainText(plaintext);
    encryptPlayfair(plaintext, matrix, ciphertext);
    printf("Encrypted message:\n%s\n", ciphertext);
    return 0;
}
