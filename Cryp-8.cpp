#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generateCipherAlphabet(char keyword[], char cipher[]) {
    int i, j;
    int keywordLength = strlen(keyword);
    int index = 0;
    for (i = 0; i < 26; ++i) {
        cipher[i] = ' ';
    }
    for (i = 0; i < keywordLength; ++i) {
        if (!isalpha(keyword[i])) {
            continue;
        }
        char letter = toupper(keyword[i]);
        if (cipher[letter - 'A'] == ' ') {
            cipher[letter - 'A'] = letter;
        }
    }
    for (i = 0; i < 26; ++i) {
        if (cipher[i] == ' ') {
            cipher[i] = 'A' + index;
            index++;
        }
    }
}
void encryptMonoalphabetic(char plaintext[], char cipher[]) {
    int i;
    int len = strlen(plaintext);
    for (i = 0; i < len; ++i) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            plaintext[i] = cipher[toupper(plaintext[i]) - 'A'] + (base - 'A');
        }
    }
}
int main() {
    char plaintext[100];
    char keyword[] = "CIPHER"; 
    char cipher[26];
    generateCipherAlphabet(keyword, cipher);
    printf("Enter the plaintext to encrypt (uppercase/lowercase letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    encryptMonoalphabetic(plaintext, cipher);
    printf("Encrypted message: %s\n", plaintext);
    return 0;
}
