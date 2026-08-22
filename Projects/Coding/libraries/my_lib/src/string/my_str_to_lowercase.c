#include "my_string.h"

char *my_str_to_lowercase(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        i++;
    }
    return (str);
}

