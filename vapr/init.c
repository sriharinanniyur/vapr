#include <math.h>
#include "vapor.h"
#include "y.tab.h"

static struct {
	char *name;
	double cval;
} consts[] = {
	"PI", 3.14159,
	"E", 2.71828,
	"GAMMA", 0.57722,
	"DEG", 57.29578,
	"PHI", 1.61803,
	0, 0
};

static struct {
	char *name;
	double (*func)();
} builtins[] = {
	"sin", sin,
	"cos", cos, 
	"atan", atan,
	"log", log,
	"log10", log10,
	"exp", exp,
	"sqrt", sqrt,
	"abs", fabs,
	0, 0
};

static struct {
	char *name;
	int kval;
} keywords[] = {
	"if", IF,
	"else", ELSE,
	"while", WHILE,
	"print", PRINT,
	"printline", PRINTLN,
	0, 0
};

void init(void)
{
	int i;
	Symbol *s;
	for (i = 0; consts[i].name; i++)
		install(consts[i].name, VAR, consts[i].cval);
	for (i = 0; builtins[i].name; i++) {
		s = install(builtins[i].name, BLTIN, 0.0);
		s->u.ptr = builtins[i].func;
	}
	for (i = 0; keywords[i].name; i++)
		install(keywords[i].name, keywords[i].kval, 0.0);
}
