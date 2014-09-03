
#ifndef VERBOSE
#define VERBOSE
char verbose;
#endif

void pushi(stack *, int);
void pushf(stack *, float);

void pushvar(stack *, var *);

void popvar(frame *, stack *, unsigned char);
void addi(stack *);
void addf(stack *);
void subi(stack *);
int lti(stack *);
int lei(stack *);
int gti(stack *);
int gei(stack *);
