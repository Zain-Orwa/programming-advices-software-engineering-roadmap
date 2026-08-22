#include "my_string.h"

size_t my_strlen(const char *str)
{
    size_t num;

    if (!str)
        return (0);
    num = 0;
    while (str[num])
        num++;
    return (num);
}

