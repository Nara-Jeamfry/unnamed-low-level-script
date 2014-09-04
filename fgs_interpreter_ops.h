
#ifndef VERBOSE
#define VERBOSE
char verbose;
#endif

#ifndef INT_OPS
#define INT_OPS
void pushi(stack *, int);
void pushf(stack *, float);
void pushs(stack *, char *);

void pushvar(stack *, var);

void popvar(frame *, stack *, unsigned char);

void operate(stack *, int type);

void addi(stack *);
void subi(stack *);
void muli(stack *);
void divi(stack *);

void addf(stack *);
void subf(stack *);
void mulf(stack *);
void divf(stack *);

void adds(stack *);

int lti(stack *);
int lei(stack *);
int gti(stack *);
int gei(stack *);
int neq(stack *);
int eq(stack *);

int comp_generic(stack *, int);
#endif