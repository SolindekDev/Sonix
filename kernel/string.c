int lenstr(char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int cmpstr(char* str1, char* str2) {
    for(int i = 0; str1[i] == str2[i]; i++) {
        if (str1[i] == '\0') return 0;
        if (str2[i] == '\0') return 0;
    }
    
    return str1[0] - str2[0];
}

void revstr(char s[]) {
    int c, i, j;
    for (i = 0, j = lenstr(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

char* convinttostr(int n, char* str) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    revstr(str);
}