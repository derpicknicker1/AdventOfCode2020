#include "advent.h"

int toI(char *s) {
	int sum = 0, min = 0;
	if(*s == '-') {
		*s++;
		min++;
	}
	if(*s == '+')
		*s++;
    while (*s && *s != '\n')
        sum = sum * 10 + (*s++ - '0');
    return min?-sum:sum;
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}