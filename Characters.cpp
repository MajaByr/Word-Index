#include <stdio.h>
#include <string.h>
#include "Characters.h"

int isLetter(char* c) 
{
	if( *c == NULL || *c != '_' && (*c>'z' || *c<'A' || (*c<'a' && *c>'Z'))) return 0;
	return 1;
}

int isDigit(char* c) 
{
	if( *c > '0' && *c < '9') return 1;
	return 0;
}

int isAlpha(char* c) 
{
	if( isDigit(c) || isLetter(c) ) return 1;
	return 0;
}
