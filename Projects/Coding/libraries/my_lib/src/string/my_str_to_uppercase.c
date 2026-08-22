#include "my_string.h"

char *my_str_to_uppercase(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
        i++;
    }
    return (str);
}

