#include <stdio.h>
#include <string.h>
#include <ctype.h>
void monoalphabeticCipher(char message[], char key[]) {
    int i;
    if(strlen(key) != 26) {
        printf("Error: Key must be exactly 26 characters long (A-Z).\n");
        return;
    }
    for(i = 0; i < 26; ++i) {
        key[i] = toupper(key[i]);
    }
    for(i = 0; message[i] != '\0'; ++i) {
        if(isalpha(message[i])) {
            char base = islower(message[i]) ? 'a' : 'A';
            message[i] = key[message[i] - base];
        }
    }
}
int main() {
    char message[100];
    char key[27];  
    int i;
    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    printf("Enter the substitution key (26 letters A-Z): ");
    fgets(key, sizeof(key), stdin);
    if(message[strlen(message) - 1] == '\n')
        message[strlen(message) - 1] = '\0';
    if(key[strlen(key) - 1] == '\n')
        key[strlen(key) - 1] = '\0';
    if(strlen(key) != 26) {
        printf("Error: Key must be exactly 26 characters long (A-Z).\n");
        return 1;
    }
    monoalphabeticCipher(message, key);
    printf("Encrypted message: %s\n", message);
    return 0;
}
