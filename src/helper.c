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

int isDigit(char c) {
	if(c >= 48 && c <= 57)
		return 1;
	return 0;
}

int isHexDigit(char c) {
	if( isDigit(c) || (c >= 97 && c <= 102))
		return 1;
	return 0;
}