#include <stdio.h>
#include <string.h>  
#include <ctype.h>
void caesarCipher(char message[], int shift) {
    char ch;
    int i;
    for(i = 0; message[i] != '\0'; ++i) {
        ch = message[i];
        if(isalpha(ch)) {  
            char base = islower(ch) ? 'a' : 'A';
            ch = base + (ch - base + shift) % 26;
        }
        message[i] = ch;
    }
}
int main() {
    char message[100];
    int shift;
    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    if(message[strlen(message) - 1] == '\n')
        message[strlen(message) - 1] = '\0';
    for(shift = 1; shift <= 25; ++shift) {
        char encryptedMessage[100];
        strcpy(encryptedMessage, message);
        caesarCipher(encryptedMessage, shift);
        printf("Shift %d: %s\n", shift, encryptedMessage);
    }

    return 0;
}
