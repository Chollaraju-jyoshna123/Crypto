#include <stdio.h>
#include <string.h>
#include <ctype.h>
void decryptPlayfair(char ciphertext[], char keyMatrix[5][5]) {
    int i, j;
    int len = strlen(ciphertext);
    for (i = 0; i < len; ++i) {
        ciphertext[i] = toupper(ciphertext[i]);
    }
    i = 0;
    while (i < len) {
        if (ciphertext[i] == ciphertext[i + 1]) {
            ciphertext[i + 1] = 'X';
        }
        int row1, col1, row2, col2;
        for (j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                if (keyMatrix[j][k] == ciphertext[i]) {
                    row1 = j;
                    col1 = k;
                } else if (keyMatrix[j][k] == ciphertext[i + 1]) {
                    row2 = j;
                    col2 = k;
                }
            }
        }
        if (row1 == row2) {
            ciphertext[i] = keyMatrix[row1][(col1 + 4) % 5];
            ciphertext[i + 1] = keyMatrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            ciphertext[i] = keyMatrix[(row1 + 4) % 5][col1];
            ciphertext[i + 1] = keyMatrix[(row2 + 4) % 5][col2];
        } else {
            ciphertext[i] = keyMatrix[row1][col2];
            ciphertext[i + 1] = keyMatrix[row2][col1];
        }
        i += 2;
    }
}
int main() {
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS "
                        "KREHE GOYFI WTTTU OLKSY CAJPO "
                        "BOTEI ZONTX BYBNT GONEY CUZWR "
                        "GDSON SXBOU YWRHE BAAHY USEDQ";
    char keyMatrix[5][5] = {
        {'K', 'Y', 'P', 'T', 'H'},
        {'E', 'X', 'A', 'M', 'N'},
        {'B', 'C', 'D', 'F', 'G'},
        {'I', 'L', 'O', 'Q', 'R'},
        {'S', 'U', 'V', 'W', 'Z'}
    };
    decryptPlayfair(ciphertext, keyMatrix);
    printf("Decrypted message:\n%s\n", ciphertext);
    return 0;
}
