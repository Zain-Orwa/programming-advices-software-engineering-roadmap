#include "my_string.h"


char *my_strncat(char *dst, const char *src, size_t num){
    size_t i;
    size_t dst_len;

    dst_len = my_strlen(dst);
    i = 0;
    while (i < num && src[i])
    {
        dst[dst_len + i] = src[i];
        i++;
    }
    dst[dst_len + i] = '\0';

    return (dst);
}
