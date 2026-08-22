#include <stdio.h>
#include "my_string.h"

int main(void)
{
    char str1[] = "hello world";
    char str2[] = "42vienna";
    char str3[] = "HELLO";
    char str4[] = "hello";
    char str5[] = "salut, comment tu vas ? 42vienna";

    printf("Original str1: %s\n", str1);
    my_str_to_uppercase(str1);
    printf("Uppercase str1: %s\n\n", str1);

    printf("Original str3: %s\n", str3);
    my_str_to_lowercase(str3);
    printf("Lowercase str3: %s\n\n", str3);

    printf("Original str5: %s\n", str5);
    my_str_capitalize(str5);
    printf("Capitalized str5: %s\n\n", str5);

    printf("Is alpha (\"%s\"): %d\n", str1, my_str_is_alpha(str1));
    printf("Is numeric (\"%s\"): %d\n", str2, my_str_is_numeric(str2));
    printf("Is lowercase (\"%s\"): %d\n", str4, my_str_is_lowercase(str4));
    printf("Is uppercase (\"HELLO\"): %d\n", my_str_is_uppercase("HELLO"));
    printf("Is printable (\"%s\"): %d\n", str5, my_str_is_printable(str5));

    return (0);
}

