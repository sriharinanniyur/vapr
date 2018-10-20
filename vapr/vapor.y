%{
#include "vapor.h"
#define code2(c1, c2)	code(c1); code(c2)
#define code3(c1, c2, c3) code(c1); code(c2); code(c3)

Inst *code(Inst);
void initcode();
void execute(Inst *);
void prexpr();
void prlnexpr();

extern Inst *progp;
%}

%union {
	Symbol *sym;
	Inst *inst;
};

%token <sym> NUM PRINT PRINTLN VAR BLTIN UNDEF WHILE IF ELSE
%type <inst> stmt asgn expr stmtlist cond while if end

%right '='
%left OR
%left AND
%left GT GE LT LE EQ NE
%left '%'
%left '+' '-'
%left '*' '/'
%left UMINUS NOT
%right '^'

%%

list:
	| list '\n'
	| list asgn '\n'	{ code2(pop, STOP); return 1; }
	| list stmt '\n'	{ code(STOP); return 1; }
	| list expr '\n'	{ code2(print, STOP); return 1; }
	| list error '\n'	{ yyerrok; }
	;

asgn:	VAR '=' expr	{ $$=$3; code3(varpush, (Inst)$1, assign); }
		;

stmt:	expr	{ code(pop); }
		| PRINT expr	{ code(prexpr); $$ = $2; }
		| PRINTLN expr	{ code(prlnexpr); $$ = $2; }
		| while cond stmt end {
			($1)[1] = (Inst)$3;
			($1)[2] = (Inst)$4;
		}
		| if cond stmt end {
			($1)[1] = (Inst)$3;
			($1)[3] = (Inst)$4;
		}
		| if cond stmt end ELSE stmt end {
			($1)[1] = (Inst)$3;
			($1)[2] = (Inst) $6;
			($1)[3] = (Inst)$7;
		}
		| '{' stmtlist '}'	{ $$ = $2; }
		;

cond:	'(' expr ')'	{ code(STOP); $$ = $2; }
	;

while:	WHILE	{ $$ = code3(whilecode, STOP, STOP); }
	;

if:	IF	{ $$ = code(ifcode); code3(STOP, STOP, STOP); }
	;

end:	{ code(STOP); $$ = progp; }

stmtlist:	{ $$ = progp; }
	| stmtlist '\n'
	| stmtlist stmt
	;

expr:
	NUM	{ code2(constpush, (Inst)$1); }
	| VAR	{ code3(varpush, (Inst)$1, eval); }
	| asgn
	| BLTIN '(' expr ')'	{ $$ = $3; code2(bltin, (Inst)$1->u.ptr); }
	| '(' expr ')'	{ $$ = $2; }
	| expr '%' expr	{ code(mod); }
	| expr '+' expr	{ code(add); }
	| expr '-' expr	{ code(sub); }
	| expr '*' expr	{ code(mul); }
	| expr '/' expr	{ code(divide); }
	| expr '^' expr	{ code(power); }
	| '-' expr %prec UMINUS { code(negate); }
	| expr GT expr	{ code(gt); }
	| expr GE expr	{ code(ge); }
	| expr LT expr	{ code(lt); }
	| expr LE expr	{ code(le); }
	| expr EQ expr	{ code(eq); }
	| expr NE expr	{ code(ne); }
	| expr AND expr	{ code(and);}
	| expr OR expr	{ code(or); }
	| NOT expr	{ $$ = $2; code(not); }
	;

%%

#include <stdio.h>
#include <ctype.h>
#include <math.h>

char *progname;
int lineno = 1;

void init(void); // from init.c

int follow(int, int, int);
int yylex(void);
void yyerror(char *);

int main(int argc, char *argv[])
{
	progname = argv[0];
	init();
	for (initcode(); yyparse(); initcode())
		execute(prog);
	return 0;
}

int yylex(void)
{
	int c;
	while ((c = getchar()) == ' ' || c == '\t')
		;
	if (c == EOF)
		return 0;
	if (c == '.' || isdigit(c)) {
		double d;
		ungetc(c, stdin);
		scanf("%lf", &d);
		yylval.sym = install("", NUM, d);
		return NUM;
	}
	if (isalpha(c)) {
		Symbol *s;
		char sbuf[100], *p = sbuf;
		do {
			*p++ = c;
		} while ((c = getchar()) != EOF && isalnum(c));
		ungetc(c, stdin);
		*p = '\0';
		if ((s = lookup(sbuf)) == NULL)
			s = install(sbuf, UNDEF, 0.0);
		yylval.sym = s;
		return s->type == UNDEF ? VAR : s->type;
	}
	switch (c) {
	case '>':	return follow('=', GE, GT);
	case '<':	return follow('=', LE, LT);
	case '=':	return follow('=', EQ, '=');
	case '!':	return follow('=', NE, NOT);
	case '|':	return OR;
	case '&':	return AND;
	case '\n':	lineno++; return '\n';
	default:	return c;
	}
	return c;
}

int follow(int expect, int yes, int no)
{
	int c = getchar();
	if (c == expect) return yes;
	ungetc(c, stdin);
	return no;
}

void yyerror(char *s)
{
	fprintf(stderr, "error : %s : at line %d\n", s, lineno);
}
