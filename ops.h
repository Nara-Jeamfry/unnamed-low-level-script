#ifndef bytecode_ops
#define bytecode_ops

#define BYT_HALT 0x00
#define BYT_GOTO 0x01

#define BYT_PUSHVAR 0x10 /* 0x10 [var] - */
#define BYT_PUSHINT 0x11 /* 0x11 [int]/4bytes - */
#define BYT_PUSHFLOAT 0x12 /* 0x12 [float]/4bytes - */
#define BYT_POPVAR 0x18 /* 0x18 [var] - Takes a value from the stack and puts it into the variable specified */

#define BYT_ADDI 0x60
#define BYT_SUBI 0x61
#define BYT_MULI 0x62

#define BYT_EQ  0x70
#define BYT_NEQ 0x71
#define BYT_LTI 0x72
#define BYT_LEI 0x73
#define BYT_GTI 0x74
#define BYT_GEI 0x75
#define BYT_LTF 0x76
#define BYT_LEF 0x77
#define BYT_GTF 0x78
#define BYT_GEF 0x79

#endif