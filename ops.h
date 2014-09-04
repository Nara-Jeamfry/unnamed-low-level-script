#ifndef bytecode_ops
#define bytecode_ops

#define BYT_HALT 0x00
#define BYT_HALR 0x01 /**< 0x01 [var] - Returns a value (will be pushed onto the stack after execution). */
#define BYT_GOTO 0x02
#define BYT_CALL 0x03

#define BYT_PUSHVAR 0x10 /* 0x10 [var] - */
#define BYT_PUSHI 0x11 /* 0x11 [int]/4bytes - */
#define BYT_PUSHF 0x12 /* 0x12 [float]/4bytes - */
#define BYT_PUSHS 0x13 /* 0x13 [length] [stringbytes]/nbytes - Takes a string and puts it into the stack */
#define BYT_POPVAR 0x18 /* 0x18 [var] - Takes a value from the stack and puts it into the variable specified */

#define BYT_I2F 0x50
#define BYT_I2S 0x51
#define BYT_F2I 0x52
#define BYT_F2S 0x52

#define BYT_ADDI 0x60
#define BYT_SUBI 0x61
#define BYT_MULI 0x62
#define BYT_DIVI 0x63
#define BYT_ADDF 0x64
#define BYT_SUBF 0x65
#define BYT_MULF 0x66
#define BYT_DIVF 0x67
#define BYT_ADDS 0x68

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


#define ASSIGNMENTUN_OFFSET 5
#define ASSIGNMENTOP_OFFSET 7
#define ASSIGNMENT_OFFSET 4
#define RETURN_OFFSET 2
#define GOTO_OFFSET 2
#define IF_OP_OFFSET 7
#define CALL_OFFSET 2
#define HALT_OFFSET 1

#endif