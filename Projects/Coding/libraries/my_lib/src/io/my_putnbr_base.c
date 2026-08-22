#include "my_io.h"
#include "my_string.h"

static int my_validate_base(const char *base)
{
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
        /* reject +, -, whitespace, and control chars */
        if (base[i] == '+' || base[i] == '-' ||
            base[i] <= 32 || base[i] == 127)
            return (0);

        j = i + 1;
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

void my_putnbr_base(int num, const char *base){
    int  base_len;
    long long_num;

    if (!my_validate_base(base))
        return;

    long_num = num;
    if (long_num < 0)
    {
        my_putchar('-');
        long_num = -long_num;
    }

    base_len = my_strlen(base);
    if (long_num >= base_len)
        my_putnbr_base(long_num / base_len, base);
    my_putchar(base[long_num % base_len]);
}

