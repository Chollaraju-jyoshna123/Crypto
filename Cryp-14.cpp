#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ALPHABET_SIZE 26
void encrypt(char plaintext[], int key[], int key_length) {
    int i = 0;
    while (plaintext[i] != '\0') {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            int shift = key[i % key_length];
            plaintext[i] = 'a' + (plaintext[i] - 'a' + shift) % ALPHABET_SIZE;
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int shift = key[i % key_length];
            plaintext[i] = 'A' + (plaintext[i] - 'A' + shift) % ALPHABET_SIZE;
        }
        i++;
    }
}
void decrypt(char ciphertext[], int key[], int key_length) {
    int i = 0;
    while (ciphertext[i] != '\0') {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            int shift = key[i % key_length];
            int decrypted_char = ciphertext[i] - 'a' - shift;
            if (decrypted_char < 0) {
                decrypted_char += ALPHABET_SIZE;
            }
            ciphertext[i] = 'a' + decrypted_char;
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int shift = key[i % key_length];
            int decrypted_char = ciphertext[i] - 'A' - shift;
            if (decrypted_char < 0) {
                decrypted_char += ALPHABET_SIZE;
            }
            ciphertext[i] = 'A' + decrypted_char;
        }
        i++;
    }
}
int main() {
    char plaintext[1000];
    int key[1000];
    int key_length;
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    srand(time(NULL));  
    printf("Key stream generated: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        int random_shift = rand() % ALPHABET_SIZE;
        key[i] = random_shift;
        printf("%d ", key[i]);
    }
    printf("\n");
    key_length = strlen(plaintext) - 1; 
    encrypt(plaintext, key, key_length);
    printf("Encrypted ciphertext: %s\n", plaintext);
    decrypt(plaintext, key, key_length);
    printf("Decrypted plaintext: %s\n", plaintext);
    return 0;
}
