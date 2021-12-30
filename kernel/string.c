#include "string.h"

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

int strcmp(char s1[], char s2[]) {
    int length_s1 = strlen(s1);
    int length_s2 = strlen(s2);

    if (length_s1 == length_s2) {
        for (int i = 0; i < length_s1; i++) {
            if (s1[i] != s2[i]) {
                return 0;
            }
        }
    } else {
        return 0;
    }

    return 1;
}