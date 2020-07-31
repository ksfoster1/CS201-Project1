#define _CRT_NONSTDC_NO_WARNINGS //because visual studio
#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS_GLOBALS 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> //for that fatal stuff
#include <string.h>
#include <ctype.h>
#include "calculon.h"
#include "value.h"
#include "node.h"
#include "queue.h"
#include "stack.h"
#include "scanner.h"
#include "convert.h"
#include "BST.h"


//* options        *

//* option         *
//* option -v      *
//* option -d      *
//* option -d YYYY *

//BSTNode *b = NULL;

int str = 0; //flag so that i know its a string

char *isString(FILE *fp)
{
	char *v;
	if (stringPending(fp))
	{
		v = readString(fp);
		//char *p = "\"";
		//strcat(v, p); //append " so that I know that it is a string
		str = 1;
		return v;
	}	
	else
		v = readToken(fp);
		

	return v;
}

int main(int argc, char **argv)
{
	int argIndex = ProcessOptions(argc, argv);
	FILE *fp;

	if (argc == 2)
	{
		fp = fopen(argv[1], "r");
	}
	else
		fp = stdin;

	BSTNode *b = NULL;
	Stack *ss = createStack();
	ss = calc(fp, b);
	fclose(fp);
}

Stack *calc(FILE *fp, BSTNode *b) //returns literal
{
	char *v;
	v = isString(fp);
	Stack *s = createStack();
	Queue *q = createQueue();
	Value *value = newValue();

	printf("\n Token is %s", v);
	//problem : was checking for feof(fp) instead of v 
	while (v != 0 && v != NULL)
	{
		char *tempValue = ""; //hold var name
		int var = 0;
		if (strcmp(v, "var") == 0)
		{
			tempValue = isString(fp); //this should be the variable name
			printf("\n VARIABLE IS: %s", tempValue);

			v = isString(fp); //this should be the =
			v = isString(fp); //this should be variable value
			printf("%s", v);
			var = 1;
		}

		if (str == 1 && strcmp(v, ";") != 0) //it is just a string //test this
		{
			printf("GGGG");
			value = newValueS(v);
			displayValue(value);
			if (var == 1)
			{
				b = insert(b, tempValue, value); //send to BST the special value
				Inorder(b);
				value = newValueV(tempValue);
				enqueue(q, value); //put value holder in main queue
			}
			else
				enqueue(q, value);
		}

		else if ((strchr(v, '.') != NULL)) //check if real number
		{
			printf("\n Found Real Number");
			double f = atof(v);
			value = newValueR(f);
			displayValue(value);
			if (var == 1)
				{
					b = insert(b, tempValue, value); //send to BST the special value
					Inorder(b);
					value = newValueV(tempValue);
					enqueue(q, value); //put value holder in main queue
				}
			else
				enqueue(q, value);
			printQ(q);
			}
		else if ((atoi(v) != 0) || (strcmp(v, "0") == 0)) //check if integer
		{
			int i = atoi(v);
			value = newValueI(i);
			displayValue(value);
			if (var == 1)
			{
				printf("{{{{{");
				b = insert(b, tempValue, value); //send to BST the special value
					Inorder(b);
					value = newValueV(tempValue);
					enqueue(q, value); //put value holder in main queue
			}
			else
				enqueue(q, value);
				//printQ(q);
			}
		else if (strcmp(v, "+") == 0 || strcmp(v, "-") == 0 || strcmp(v, "*") == 0 //check if an operator
				|| strcmp(v, "/") == 0 || strcmp(v, "%") == 0 || strcmp(v, "^") == 0
				|| strcmp(v, "(") == 0 || strcmp(v, ")") == 0)
		{
				value = newValueS(v);
				displayValue(value);
				enqueue(q, value);
				//printQ(q);
		}

		else if (strcmp(v, ";") == 0)
		{
			s = infix_to_postfix(q);
			reverseStack(s);
			q = createQueue(); //restarts queue
		}

		else
			{
				Inorder(b);
				Value *y = newValue();
				y = search(b, v);
				displayValue(y);
				if ((y->type == 2) && (strcmp(y->sval, "Tree is empty") == 0))
				{
					printf("Variable %s was not declared", v);
					exit(0);
				}
					
				else
				{
					char *H = v; //save var for checking later
					Queue *tempQ = createQueue();
					v = isString(fp);
					printf("TTT IS %s", v);
					if (strcmp(v, "=") != 0)
						break;
					else
					while (v != 0 && v!= NULL)
					{
						v = isString(fp);
						printf("TTT IS %s", v);

						if (str == 1 && strcmp(v, ";") != 0) //it is just a string //test this
						{
							printf("GGGG");
							value = newValueS(v);
							displayValue(value);
							enqueue(tempQ, value);
						}

						else if ((strchr(v, '.') != NULL)) //check if real number
						{
							printf("\n Found Real Number");
							double f = atof(v);
							value = newValueR(f);
							displayValue(value);
							enqueue(tempQ, value);
							//printQ(q);
						}
						else if ((atoi(v) != 0) || (strcmp(v, "0") == 0)) //check if integer
						{
							int i = atoi(v);
							value = newValueI(i);
							displayValue(value);
							enqueue(tempQ, value);
							//printQ(q);
						}
						else if (operator(v) == 1)
						{
							value = newValueS(v);
							displayValue(value);
							enqueue(tempQ, value);
							//printQ(q);
						}

						else if (strcmp(v, "=") == 0)
						{
							continue;
						}

						else if (strcmp(v, ";") == 0)
						{
							printf("SSS");
							printf("\n QUEUE ::::");
							printQ(tempQ);
							Stack *tempStack = createStack();
							tempStack = infix_to_postfix(tempQ);
							reverseStack(tempStack);
							printf("\n POSTFIX IS");
							printS(tempStack);
							tempStack = postfix_to_literal(tempStack, b);
							printf("\n LITERAL IS");
							printS(tempStack);
							Value *temp = newValue();
							temp = pop(tempStack);
							insert(b, H, temp);
							printf("\n BST ::::");
							Inorder(b);
							printf("\n MMMMMMM: ");
							displayValue(temp);
							enqueue(q, temp);
							tempQ = createQueue(); //restarts queue
							q = createQueue();
							break;
						}
						else
						{
							printf("RRRR");
							value = newValueV(v);
							displayValue(value);
							enqueue(tempQ, value);
						}
					}


				}
			}
		printf("EEEE");
		v = isString(fp);
		printf("\n Token is %s", v);
	}
	printf("postfix is : ");
	printS(s);
	s = postfix_to_literal(s, b);
	printf("literal is :");
	printS(s);
	return s;
}

Stack *calc2(FILE *fp, BSTNode *b) //returns postfix
{
	char *v;
	v = isString(fp);
	Stack *s = createStack();
	Queue *q = createQueue();
	Value *value = newValue();

	printf("\n Token is %s", v);
	//problem : was checking for feof(fp) instead of v 
	while (v != 0 && v != NULL)
	{
		char *tempValue = ""; //hold var name
		int var = 0;
		if (strcmp(v, "var") == 0)
		{
			tempValue = isString(fp); //this should be the variable name
			printf("\n VARIABLE IS: %s", tempValue);

			v = isString(fp); //this should be the =
			v = isString(fp); //this should be variable value
			printf("%s", v);
			var = 1;
		}

		if (strchr(v, '\"') != NULL) //it is just a string //test this
		{
			value = newValueS(v);
			displayValue(value);
			if (var == 1)
			{
				b = insert(b, tempValue, value); //send to BST the special value
				Inorder(b);
				value = newValueV(tempValue);
				enqueue(q, value); //put value holder in main queue
			}
			else
				enqueue(q, value);
		}

		else if ((strchr(v, '.') != NULL)) //check if real number
		{
			printf("\n Found Real Number");
			double f = atof(v);
			value = newValueR(f);
			displayValue(value);
			if (var == 1)
			{
				b = insert(b, tempValue, value); //send to BST the special value
				Inorder(b);
				value = newValueV(tempValue);
				enqueue(q, value); //put value holder in main queue
			}
			else
				enqueue(q, value);
			printQ(q);
		}
		else if ((atoi(v) != 0) || (strcmp(v, "0") == 0)) //check if integer
		{
			int i = atoi(v);
			value = newValueI(i);
			displayValue(value);
			if (var == 1)
			{
				printf("{{{{{");
				b = insert(b, tempValue, value); //send to BST the special value
				Inorder(b);
				value = newValueV(tempValue);
				enqueue(q, value); //put value holder in main queue
			}
			else
				enqueue(q, value);
			//printQ(q);
		}
		else if (strcmp(v, "+") == 0 || strcmp(v, "-") == 0 || strcmp(v, "*") == 0 //check if an operator
			|| strcmp(v, "/") == 0 || strcmp(v, "%") == 0 || strcmp(v, "^") == 0
			|| strcmp(v, "(") == 0 || strcmp(v, ")") == 0 || strcmp(v, "=") == 0)
		{
			value = newValueS(v);
			displayValue(value);
			enqueue(q, value);
			//printQ(q);
		}

		else if (strcmp(v, ";") == 0)
		{
			s = infix_to_postfix(q);
			reverseStack(s);
			q = createQueue(); //restarts queue
		}

		else //variable name without a var
		{
			Inorder(b);
			printf("WWWW");
			Value *y = newValue();
			y = search(b, v);
			displayValue(y);
			if (y == NULL)
				printf("Variable %s was not declared", v);
			else
			{
				value = newValueV(v);
				displayValue(value);
				enqueue(q, value);
			}
		}
		printf("EEEE");
		v = isString(fp);
		printf("\n Token is %s", v);
	}
	printf("postfix is : ");
	printS(s);
	return s;
}
//* only -oXXX  or -o XXX options *

int ProcessOptions(int argc, char **argv)
{
	FILE *fp;
	int argIndex;
	int argUsed;
	int separateArg;
	char *arg;

	argIndex = 1;

	while (argIndex < argc && *argv[argIndex] == '-')
	{
		//* check if stdin, represented by "-" is an argument *
		//* if so, the end of options has been reached *
		if (argv[argIndex][1] == '\0') return argIndex;

		separateArg = 0;
		argUsed = 0;

		if (argv[argIndex][2] == '\0')
		{
			arg = argv[argIndex + 1];
			separateArg = 1;
		}
		else
			arg = argv[argIndex] + 2;

		switch (argv[argIndex][1])
		{
		case 'v': //gives author's name and exit
			printf("Kenya S. Foster\n");
			exit(0);
		case 'd':
			printf("%d", argc);
			if (argc == 3)
			{
				fp = fopen(argv[2], "r");
				BSTNode *b = NULL;
				Stack *ss = createStack();
				ss = calc2(fp, b);
				argUsed = 1;
			}
			
			else
			{
				fp = stdin;
				BSTNode *b = NULL;
				Stack *ss = createStack();
				ss = calc2(fp, b);
			}
			exit(0);
		default:
			Fatal("option %s not understood\n", argv[argIndex]);
		}
		if (separateArg && argUsed)
			++argIndex;
		++argIndex;
	}
	return argIndex;
	fclose(fp);
}