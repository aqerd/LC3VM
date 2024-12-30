#include <stdint.h>
#include "lc3.h"

void do_ADD(uint16_t instr, uint16_t reg[]) {
    uint16_t r0 = (instr >> 9) & 0x7; /* DR */
    uint16_t r1 = (instr >> 6) & 0x7; /* SR1 */
    uint16_t imm_flag = (instr >> 5) & 0x1; /* are we in immediate mode? */

    /* if we are in immediate mode */
    if (imm_flag) {
        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
        reg[r0] = reg[r1] + imm5;
    } 
    /* we are in register mode */
    else {
        uint16_t r2 = instr & 0x7;
        reg[r0] = reg[r1] + reg[r2];
    }
    update_flags(r0);
}

void do_AND(uint16_t instr, uint16_t reg[]) {
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t r1 = (instr >> 6) & 0x7;
    uint16_t imm_flag = (instr >> 5) & 0x1;

    if (imm_flag) {
        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
        reg[r0] = reg[r1] & imm5;
    } else {
        uint16_t r2 = instr & 0x7;
        reg[r0] = reg[r1] & reg[r2];
    }
    update_flags(r0);
}

void do_BR(uint16_t instr, uint16_t reg[]) {
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    uint16_t cond_flag = (instr >> 9) & 0x7;
    if (cond_flag & reg[R_COND])
    {
        reg[R_PC] += pc_offset;
    }
}

void do_NOT(uint16_t instr, uint16_t reg[]) {
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t r1 = (instr >> 6) & 0x7;
    reg[r0] = ~reg[r1];
    update_flags(r0);
}

void do_LDI(uint16_t instr, uint16_t reg[]) {
    /* add PCoffset9 to the current PC, look at that memory location to get the final address */
    uint16_t r0 = (instr >> 9) & 0x7; /* DR */
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9); /* PCoffset9 */
    reg[r0] = mem_read(mem_read(reg[R_PC] + pc_offset)); 
    update_flags(r0);
}

void do_JMP(uint16_t instr, uint16_t reg[]) {
    /* Also handles RET */
    uint16_t r1 = (instr >> 6) & 0x7;
    reg[R_PC] = reg[r1];
}

void do_RET(uint16_t instr, uint16_t reg[]) {
    /* RET happens whenever R1 is 7, it's actually a special case of JMP */
    do_JMP(instr, reg);
}

void do_JSR(uint16_t instr, uint16_t reg[]) {
    uint16_t long_flag = (instr >> 11) & 1;
    reg[R_R7] = reg[R_PC];
    if (long_flag)
    {
        uint16_t long_pc_offset = sign_extend(instr & 0x7FF, 11);
        reg[R_PC] += long_pc_offset;  /* JSR */
    }
    else
    {
        uint16_t r1 = (instr >> 6) & 0x7;
        reg[R_PC] = reg[r1]; /* JSRR */
    }
}

void do_LD(uint16_t instr, uint16_t reg[]) {
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    reg[r0] = mem_read(reg[R_PC] + pc_offset);
    update_flags(r0);
}

void do_LDR(uint16_t instr, uint16_t reg[]) {
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t r1 = (instr >> 6) & 0x7;
    uint16_t offset = sign_extend(instr & 0x3F, 6);
    reg[r0] = mem_read(reg[r1] + offset);
    update_flags(r0);
}

void do_LEA(uint16_t instr, uint16_t reg[]) {
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    reg[r0] = reg[R_PC] + pc_offset;
    update_flags(r0);
}

void do_ST(uint16_t instr, uint16_t reg[]) {
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    mem_write(reg[R_PC] + pc_offset, reg[r0]);
}

void do_STR(uint16_t instr, uint16_t reg[]) {
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t r1 = (instr >> 6) & 0x7;
    uint16_t offset = sign_extend(instr & 0x3F, 6);
    mem_write(reg[r1] + offset, reg[r0]);
}

void do_STI(uint16_t instr, uint16_t reg[]) {
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    mem_write(mem_read(reg[R_PC] + pc_offset), reg[r0]);
}

void do_TRAP(uint16_t instr, uint16_t reg[], int running) {
    reg[R_R7] = reg[R_PC];

    switch (instr & 0xFF) {
        case TRAP_GETC:
            trap_getc(reg);
            break;
        case TRAP_OUT:
            trap_out(reg);
            break;
        case TRAP_PUTS:
            trap_puts(reg);
            break;
        case TRAP_IN:
            trap_in(reg);
            break;
        case TRAP_PUTSP:
            trap_putsp(reg);
            break;
        case TRAP_HALT:
            trap_halt(running);
            break;
    }
}
