#include "my_string.h"

/*
    Returns: initial length of dst + length of src.
    If num <= dst_len, returns num + src_len (means truncation happened).
    Always NUL-terminates if num > 0.
*/

size_t my_strlcat(char *dst, const char *src, size_t size){
    size_t dst_len;
    size_t src_len;
    size_t i;

    if (!dst || !src)
        return (0);

    dst_len = my_strlen(dst);
    src_len = my_strlen(src);

    if (size == 0)
        return (src_len);

    if (size <= dst_len)
        return (size + src_len);

    i = 0;
    while (src[i] && (dst_len + i + 1) < size)
    {
        dst[dst_len + i] = src[i];
        i++;
    }
    dst[dst_len + i] = '\0';

    return (dst_len + src_len);
}
