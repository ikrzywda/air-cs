#include <stdio.h>
#include <stdlib.h>

#define LENGTH 100

char *concat(char p[LENGTH], char q[LENGTH]) {

    char *start_ptr = p;

    for (; *p != '\0'; ++p);
    for (; *q != '\0'; *(p++) = *q++);

    *p = '\0';
    return start_ptr;
}

int main() {

    char str1[LENGTH] = "Hello, ";
    char str2[LENGTH] = "world!";

    printf("%s\n", concat(str1, str2));

    return 0;
}
