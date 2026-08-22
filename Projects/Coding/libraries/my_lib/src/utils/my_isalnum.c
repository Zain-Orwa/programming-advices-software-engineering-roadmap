#include "my_utils.h"

int my_isalnum(int c)
{
    return (my_isalpha(c) || my_isdigit(c));
}

