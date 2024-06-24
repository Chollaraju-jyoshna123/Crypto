#include <stdio.h>
#include<string.h>
#include <ctype.h>
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; 
}
void affineCipherEncrypt(char message[], int a, int b) {
    int i;
    int len = strlen(message);
    for (i = 0; i < len; ++i) {
        if (isalpha(message[i])) {
            char base = islower(message[i]) ? 'a' : 'A';
            message[i] = ((a * (message[i] - base) + b) % 26) + base;
        }
    }
}
int main() {
    char message[100];
    int a, b;
    printf("Enter the message to encrypt (uppercase/lowercase letters only): ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 
    printf("Enter the value of a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
    if (modInverse(a, 26) == -1) {
        printf("Error: a must be coprime with 26.\n");
        return 1;
    }
    affineCipherEncrypt(message, a, b);
    printf("Encrypted message: %s\n", message);
    return 0;
}
