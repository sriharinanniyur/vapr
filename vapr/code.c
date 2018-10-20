#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vapor.h"
#include "y.tab.h"

#define NSTACK 256

static Datum stack[NSTACK];
static Datum *stackp;

#define NPROG 2000
Inst prog[NPROG];
Inst *progp;
Inst *pc;

void initcode()
{
	stackp = stack;
	progp = prog;
}

void push(Datum d)
{
	if (stackp >= &stack[NSTACK]) {
		fprintf(stderr, "stack overflow\n");
		exit(1);
	}
	*stackp++ = d;
}

Datum pop()
{
	if (stackp <= stack) {
		fprintf(stderr, "stack underflow\n");
		exit(1);
	}
	return *--stackp;
}

Inst *code(Inst f)
{
	Inst *oprogp = progp;
	if (progp >= &prog[NPROG]) {
		fprintf(stderr, "program size exceeds memory limits\n");
		exit(1);
	}
	*progp++ = f;
	return oprogp;
}

void execute(Inst *p)
{
	for (pc = p; *pc != STOP; )
		(*(*pc++))();
}

void constpush()
{
	Datum d;
	d.val = ((Symbol *)*pc++)->u.val;
	push(d);
}

void varpush()
{
	Datum d;
	d.sym = (Symbol *)(*pc++);
	push(d);
}

void mod()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = (int)((int)d1.val % (int)d2.val);
	push(d1);
}

void add()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val += d2.val;
	push(d1);
}

void sub()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val -= d2.val;
	push(d1);
}

void mul()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val *= d2.val;
	push(d1);
}

void divide()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val /= d2.val;
	push(d1);
}

void power()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = pow(d1.val, d2.val);
    push(d1);
}

void negate()
{
	Datum d1;
	d1 = pop();
	d1.val = -d1.val;
	push(d1);
}

void eval()
{
	Datum d;
	d = pop();
	if (d.sym->type == UNDEF) {
		fprintf(stderr, "undefined variable\n");
		exit(1);
	}
	d.val = d.sym->u.val;
	push(d);
}

void assign()
{
	Datum d1, d2;
	d1 = pop();
	d2 = pop();
	if (d1.sym->type != VAR && d1.sym->type != UNDEF) {
		fprintf(stderr, "assignment to rvalue\n");
		exit(1);
	}
	d1.sym->u.val = d2.val;
	d1.sym->type = VAR;
	push(d2);
}

void print()
{
	Datum d;
	d = pop();
	printf("%.8g\n", d.val);
}

void bltin()
{
	Datum d;
	d = pop();
	d.val = (*(double(*)())(*pc++))(d.val);
	push(d);
}

void gt()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = (double)(d1.val > d2.val);
	push(d1);
}

void lt()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = (double)(d1.val < d2.val);
	push(d1);
}

void ge()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = (double)(d1.val >= d2.val);
	push(d1);
}


void le()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = (double)(d1.val <= d2.val);
	push(d1);
}

void eq()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = (double)(d1.val == d2.val);
	push(d1);
}

void ne()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = (double)(d1.val != d2.val);
	push(d1);
}

void and()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = (double)(d1.val != 0.0 && d2.val != 0.0);
	push(d1);
}

void or()
{
	Datum d1, d2;
	d2 = pop();
	d1 = pop();
	d1.val = (double)(d1.val != 0.0 || d2.val != 0.0);
	push(d1);
}

void not()
{
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = (double)(d1.val == 0.0);
    push(d1);
}

void whilecode()
{
	Datum d;
	Inst *spc = pc;
	execute(spc + 2);
	d = pop();
	while (d.val) {
		execute(*((Inst **)(spc)));
		execute(spc + 2);
		d = pop();
	}
	pc = *((Inst **)(spc + 1));
}

void ifcode()
{
	Datum d;
	Inst *spc = pc;
	execute(spc + 3);
	d = pop();
	if (d.val)
		execute(*((Inst **)(spc)));
	else if (*((Inst **)(spc+1)))
		execute(*((Inst **)(spc+1)));
	pc = *((Inst **)(spc + 2));
}

void prexpr()
{
	Datum d;
	d = pop();
	printf("%.8g\t", d.val);
}

void prlnexpr()
{
	Datum d;
	d = pop();
	printf("%.8g\n", d.val);
}
