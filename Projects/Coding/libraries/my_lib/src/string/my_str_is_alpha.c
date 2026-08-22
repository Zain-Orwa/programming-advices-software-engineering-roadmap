#include "my_string.h"

int my_str_is_alpha(const char *str){
    int i;

    i = 0;
    if (!str || !str[0])
        return (1);

    while (str[i])
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
            return (0);
        i++;
    }

    return (1);
}
