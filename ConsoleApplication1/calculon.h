#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include "stack.h"
#include "BST.h"

extern int str;
extern int ProcessOptions(int, char **);
extern Stack *calc(FILE *, BSTNode *);
extern char *isString(FILE *);
extern int main(int , char **);