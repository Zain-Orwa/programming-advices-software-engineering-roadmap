#include "my_string.h"

int my_strcmp(const char *str1, const char *str2){
    unsigned char c1;
    unsigned char c2;

    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    c1 = (unsigned char)*str1;
    c2 = (unsigned char)*str2;

    return (c1 - c2);
}
