#ifndef LC3
#define LC3

#include <stdint.h>

uint16_t reg[R_COUNT];

enum {
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,
    R_COND,
    R_COUNT
};

enum {
    FL_POS = 1 << 0,
    FL_ZRO = 1 << 1,
    FL_NEG = 1 << 2,
};

enum {
    OP_BR = 0,  /* branch */
    OP_ADD,     /* add  */
    OP_AND,     /* bitwise and */
    OP_JMP,     /* jump */
    OP_JSR,     /* jump register */
    OP_LD,      /* load */
    OP_LDI,     /* load indirect */
    OP_LDR,     /* load register */
    OP_LEA,     /* load effective address */
    OP_NOT,     /* bitwise not */
    OP_ST,      /* store */
    OP_STI,     /* store indirect */
    OP_STR,     /* store register */
    OP_RTI,     /* unused */
    OP_TRAP,    /* execute trap */
    OP_RES      /* reserved (unused) */
};

#endif