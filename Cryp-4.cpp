#include <stdio.h>
#include <string.h>
#include <ctype.h>
void vigenereCipher(char message[], char key[]) {
    int i, j;
    int keyLength = strlen(key);
    int msgLength = strlen(message);
    char encryptedMessage[msgLength];
    for (i = 0, j = 0; i < msgLength; ++i) {
        char currentChar = message[i];
        char k = key[j % keyLength];
        if (isalpha(currentChar)) {
            char base = islower(currentChar) ? 'a' : 'A';
            encryptedMessage[i] = base + (currentChar - base + (k - 'A')) % 26;
            ++j;
        } else {
            encryptedMessage[i] = currentChar; 
        }
    }
    strcpy(message, encryptedMessage);
}
int main() {
    char message[100];
    char key[100];
    printf("Enter the message to encrypt (uppercase/lowercase letters only): ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 
    printf("Enter the key (uppercase letters only): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    vigenereCipher(message, key);
    printf("Encrypted message: %s\n", message);
    return 0;
}
