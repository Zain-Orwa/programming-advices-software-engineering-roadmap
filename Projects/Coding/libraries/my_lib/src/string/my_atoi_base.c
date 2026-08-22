#include "my_string.h"

static int my_validate_base(const char *base){
    int i;
    int j;
    int base_len;

    if (!base)
        return (0);

    base_len = my_strlen(base);
    if (base_len <= 1)
        return (0);

    i = 0;
    while (base[i])
    {
        if (base[i] == '+' || base[i] == '-' || base[i] <= 32 || base[i] == 127)
            return (0);

        j = i + 1;//we are branching here//
        while (base[j])
        {
            if (base[i] == base[j])
                return (0);
            j++;
        }
        i++;
    }

    return (1);
}

static int my_base_index(char c, const char *base){
    int i;

    i = 0;
    while (base[i])
    {
        if (base[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

int my_atoi_base(const char *str, const char *base){
    int base_len;
    int sign;
    int result;
    int digit;

    if (!my_validate_base(base))
        return (0);

    base_len = my_strlen(base);
    sign     = 1;
    result   = 0;

    while (*str && (*str <= 32))
        str++;

    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }

    digit = my_base_index(*str, base);
    while (digit != -1)
    {
        result = (result * base_len) + digit;
        str++;
        digit = my_base_index(*str, base);
    }

    return (result * sign);
}

