#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    char * p;
    size_t p_length = (6 * (sizeof(char)));
    p = (char*)malloc(6);

    if(p == NULL) {
        printf("p is NULL!");
        return 1;
    }
    p[0] = 'a';
    p[1] = 'b';
    p[2] = 'c';
    p[3] = 'd';
    p[4] = 'e';
    p[5] = 'f';
    printf("String = %s,  Address = %u\n", p, p);
    printf("last char : %c ", p[6]);
    free(p);


    // Dynamically allocated arrays need to have their size monitored.
    // There is no way to know unless it is saved somehow.

    return 0;
}




//eof
