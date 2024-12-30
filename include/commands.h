#ifndef COMMANDS
#define COMMANDS

#include <stdint.h>

void do_ADD(uint16_t instr, uint16_t reg[]);
void do_AND(uint16_t instr, uint16_t reg[]);
void do_NOT(uint16_t instr, uint16_t reg[]);
void do_BR(uint16_t instr, uint16_t reg[]);
void do_JMP(uint16_t instr, uint16_t reg[]);
void do_JSR(uint16_t instr, uint16_t reg[]);
void do_LD(uint16_t instr, uint16_t reg[]);
void do_LDI(uint16_t instr, uint16_t reg[]);
void do_LDR(uint16_t instr, uint16_t reg[]);
void do_LEA(uint16_t instr, uint16_t reg[]);
void do_ST(uint16_t instr, uint16_t reg[]);
void do_STI(uint16_t instr, uint16_t reg[]);
void do_STR(uint16_t instr, uint16_t reg[]);
void do_TRAP(uint16_t instr, uint16_t reg[]);

#endif