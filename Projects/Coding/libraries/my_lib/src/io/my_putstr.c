#include "my_io.h"

void my_putstr(const char *str)
{
    if (!str)
        return;
    while (*str)
        write(1, str++, 1);
}

