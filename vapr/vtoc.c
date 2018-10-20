/* vtoc.c - Convert Vapor code to voice command text. */
/* Written by Srihari Nanniyur. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void convert(FILE *);

int main(int argc, char *argv[])
{
	if (argc == 1) convert(stdin);
	while (--argc > 0) {
		FILE *inp = fopen(*++argv, "r");
		if (inp == NULL) {
			fprintf(stderr, "file not found\n");
			exit(EXIT_FAILURE);
		}
		convert(inp);
		fclose(inp);
	}
	return 0;
}

void convert(FILE *in)
{
	int c;
	while ((c = getc(in)) != EOF) {
		switch (c) {
		case '{':	printf(" begin "); break;
		case '}':	printf(" terminate "); break;
		case '(':	printf(" start "); break;
		case ')':	printf(" stop "); break;
		case '%':	printf(" modulus "); break;
		case '+':	printf(" plus "); break;
		case '-':	printf(" minus "); break;
		case '*':	printf(" times "); break;
		case '/':	printf(" over "); break;
		case '^':	printf(" power "); break;
		case '=':	printf(" equals "); break;
		case '>':	printf(" greater "); break;
		case '<':	printf(" less "); break;
		case '|':	printf(" or" ); break;
		case '&':	printf(" and "); break;
		case '!':	printf(" not "); break;
		case '\n':	printf(" return");
		default:	putchar(c);
		}
	}
}
