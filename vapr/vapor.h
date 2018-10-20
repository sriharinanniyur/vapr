#ifndef __vapor_vapor_h__
#define __vapor_vapor_h__

typedef struct Symbol {
	char *name;
	short type;
	union {
		double val;
		double (*ptr)();
	} u;
	struct Symbol *next;
} Symbol;

Symbol *lookup(char *);
Symbol *install(char *, int, double);

typedef union Datum {
	double val;
	Symbol *sym;
} Datum;

extern Datum pop();

typedef void (*Inst)();
#define STOP (Inst) 0

extern Inst prog[];
extern void  eval(), mod(), add(), sub(), mul(), divide(), negate(), power();
extern void assign(), bltin(), varpush(), constpush(), print();
extern void prexpr();
extern void gt(), lt(), eq(), ge(), le(), ne(), and(), or(), not();
extern void ifcode(), whilecode();

#endif
