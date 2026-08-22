#include "my_string.h"

int my_str_is_numeric(const char *str)
{
    int i;

    i = 0;
    if (!str || !str[0])
        return (1);
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

