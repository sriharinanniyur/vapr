/* ctov.c - convert voice commands to Vapor code. */
/* Written by Srihari Nanniyur. */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char line[512];
	while ((fgets(line, 512, stdin))) {
		char *token = strtok(line, " \n");
		while (token != NULL) {
			if (strcmp(token, "return") == 0)
				putchar('\n');
			else if (strcmp(token, "begin") == 0)
				putchar('{');
			else if (strcmp(token, "terminate") == 0)
				putchar('}');
			else if (strcmp(token, "start") == 0)
				putchar('(');
			else if (strcmp(token, "stop") == 0)
				putchar(')');
			else if (strcmp(token, "plus") == 0)
				putchar('+');
			else if (strcmp(token, "minus") == 0)
				putchar('-');
			else if (strcmp(token, "times") == 0)
				putchar('*');
			else if (strcmp(token, "over") == 0)
				putchar('/');
			else if (strcmp(token, "mod") == 0)
				putchar('%');
			else if (strcmp(token, "power") == 0)
				putchar('^');
			else if (strcmp(token, "equals") == 0
				|| strcmp(token, "equal") ==0)
				putchar('=');
			else if (strcmp(token, "greater") == 0)
				putchar('>');
			else if (strcmp(token, "less") == 0)
				putchar('<');
			else if (strcmp(token, "or") == 0)
				putchar('|');
			else if (strcmp(token, "and") == 0)
				putchar('&');
			else if (strcmp(token, "not") == 0)
				putchar('!');
			else if (strcmp(token, "zero") == 0)
				putchar('0');
			else if (strcmp(token, "one") == 0)
				putchar('1');
			else if (strcmp(token, "two") == 0 || strcmp(token, "to") == 0
				|| strcmp(token, "too") == 0)
				putchar('2');
			else if (strcmp(token, "three") == 0)
				putchar('3');
			else if (strcmp(token, "four") == 0 || strcmp(token, "for") == 0
				|| strcmp(token, "fore") == 0)
				putchar('4');
			else if (strcmp(token, "five") == 0)
				putchar('5');
			else if (strcmp(token, "six") == 0)
				putchar('6');
			else if (strcmp(token, "seven") == 0)
				putchar('7');
			else if (strcmp(token, "eight") == 0)
				putchar('8');
			else if (strcmp(token, "nine") == 0)
				putchar('9');
			else if (strcmp(token, "print") == 0
				|| strcmp(token, "great") == 0)
				printf("print");
			else
				printf("%s", token);
			token = strtok(NULL, " \n");
		}
	}
	return 0;
}
