#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	//char a[] = "Cat";
	//printf("%zu %zu\n", sizeof(a), strlen(a));
	
	//char s[] = "code";
	//printf("%c %c %c %c\n", *(&s[0]+ 3), *(&s[0] + 2), *(&s[0] + 1), *(&s[0] + 0));
	//printf("%c %c %c %c\n", *(s + 3), *(s + 2), *(s + 1), *(s + 0));
	
	/*char s[] = "code";
	for (char *p = s + strlen(s) - 1; p >= s; --p) putchar(*p);
	//best way:
	size_t len = strlen(s);
	if (len) {
    for (char *p = s + len - 1; p >= s; --p)
        putchar((unsigned char)*p);
	}*/

	/*char *titles[] = {"Hamlet", "Odyssey"};
	size_t size = sizeof(titles) / sizeof(titles[0]);
	for (size_t i = 0; i < size; i++){
		printf("%s\n", titles[i]);
	}
	//Another way:
	for (size_t i=0;i<sizeof(titles)/sizeof(*titles);++i) puts(titles[i]);
	*/

	//char *lit = "edit"; //unmodifyable cause read-only UB;
	char buf[] = "edit";
	buf[0] = 'E';
	buf[1] = 'D';
	buf[2] = 'I';
	buf[3] = 'T';

	size_t len = strlen(buf);
	for (size_t i = 0; i < len; i++){
		printf("%c", buf[i]);
	}


	return (0);
}
