#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 99999
#define MAXWORD 256
#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

int getword(char **, int *);
int mygetline(char **line);
char *mystrdup(char *s);

#endif
