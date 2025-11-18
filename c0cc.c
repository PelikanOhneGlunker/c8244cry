#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int CHARMIN = -128;
int CHARMAX = 127;

const char NULLPTR = '\0';

char add(char a, char b);
char sub(char a, char b);
char getLength(char p1, char p2);

#ifdef PLATFORM_ESP8266
void pri(char cc = 0, char *ptrMsg) {
    if (cc != 0) {
        Serial.printf(" ==> %d\n", cc);
    } else {
        printf(" --> %u\n", *ptrMsg);
    }

}
#endif

void encrypt(const char *text, const char *key, size_t length) {
    for (size_t i = 0; i < length; i++) {
        add(text, key);
    }
}

void decrypt(const char *text, const char *key, size_t length) {
    for (size_t i = 0; i < length; i++) {
        sub(text, key);
    }
}

char add(char *a, char *b) {
    int c = int(*a) + int(*b);
    if (c > CHARMAX) {
        c = c - CHARMAX - 1;
    }
    char d = char(c);
    *a = d;
}

char sub(char a, char b) {
    int c = int(*a) - int(*b);
    if (c < 0) {
        c = c + CHARMAX + 1;
    }
    char d = char(c);
    *a = d;
}

char getLength(char p1, char p2) {
    if (p1 == p2) {
        return p1;
    } else {
        if (p1 < p2) {
            return p1;
        } else {
            return p2;
        }
    }
}

int main() {
    char *text = "00000 HinterDerSonne#! Pin:74958768957987893 Meine gehaime Nachricht\0";
    char *keyy = "21348590243823947852389672364587362487523476587234658723645782346587\0";
    size_t length = strlen(text);
    printf("Original: %s\n", text);
    encrypt(text, keyy, length);
    printf("Encrypted: %s\n", text);
    decrypt(text, keyy, length);
    printf("Decrypted: %s\n", text);
    return 0;
}

