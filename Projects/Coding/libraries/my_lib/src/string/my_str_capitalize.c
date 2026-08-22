#include "my_string.h"

static int is_alnum(char c)
{
    return ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9'));
}

char *my_str_capitalize(char *str)
{
    int i;
    int new_word;

    i = 0;
    new_word = 1;
    while (str && str[i])
    {
        if (is_alnum(str[i]))
        {
            if (new_word && str[i] >= 'a' && str[i] <= 'z')
                str[i] -= 32;
            else if (!new_word && str[i] >= 'A' && str[i] <= 'Z')
                str[i] += 32;
            new_word = 0;
        }
        else
            new_word = 1;
        i++;
    }
    return (str);
}

