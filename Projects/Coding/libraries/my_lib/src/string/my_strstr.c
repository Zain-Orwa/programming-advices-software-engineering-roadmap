#include "my_string.h"

char *my_strstr(const char *str, const char *to_find){
    size_t to_find_len;

    if (!*to_find)
        return (char *)str;

    to_find_len = my_strlen(to_find);
    while (*str)
    {
        if (my_strncmp(str, to_find, to_find_len) == 0)
            return ((char *)str);
        str++;
    }

    return (NULL);
}
