#ifndef LC3
#define LC3

#include <stdint.h>
#include "trap.h"

#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX];

uint16_t reg[R_COUNT];

/* Registers */
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

/* Flags */
enum {
    FL_POS = 1 << 0,
    FL_ZRO = 1 << 1,
    FL_NEG = 1 << 2,
};

/* Opcodes */
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
    OP_RET,     /* return from procedure */
    OP_TRAP,    /* execute trap */
    OP_RES      /* reserved (unused) */
};

/* TRAP routines */
enum {
    TRAP_GETC = 0x20,  /* get character from keyboard, not echoed onto the terminal */
    TRAP_OUT = 0x21,   /* output a character */
    TRAP_PUTS = 0x22,  /* output a word string */
    TRAP_IN = 0x23,    /* get character from keyboard, echoed onto the terminal */
    TRAP_PUTSP = 0x24, /* output a byte string */
    TRAP_HALT = 0x25   /* halt the program */
};

#endif