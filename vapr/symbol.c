#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vapor.h"
#include "y.tab.h"

static Symbol *symlist = NULL;

Symbol *lookup(char *s)
{
	Symbol *sp;
	for (sp = symlist; sp != NULL; sp = sp->next)
		if (strcmp(sp->name, s) == 0)
			return sp;
	return NULL;
}

Symbol *install(char *s, int t, double d)
{
	Symbol *sp = (Symbol *) malloc(sizeof(Symbol));
	sp->name = (char *) malloc((strlen(s) + 1) * sizeof(char));
	if (sp == NULL || sp->name == NULL) {
		fprintf(stderr, "memory error\n");
		exit(1);
	}
	strcpy(sp->name, s);
	sp->type = t;
	sp->u.val = d;
	sp->next = symlist;
	symlist = sp;
	return sp;
}
