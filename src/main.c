#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include "littlecomputer.h"
#include "commands.h"
#include "utils.h"
#include "inputbuffering.h"
#include "lcmemory.h"

int main(int argc, const char* argv[]) {
    load_arguments(argc, argv);
    
    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    enum { PC_START = 0x3000 };
    reg[R_COND] = FL_ZRO;
    reg[R_PC] = PC_START;

    int running = 1;
    while (running) {
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;

        switch (op) {
            case OP_ADD:
                do_ADD(instr);
                break;
            case OP_AND:
                do_AND(instr);
                break;
            case OP_NOT:
                do_NOT(instr);
                break;
            case OP_BR:
                do_BR(instr);
                break;
            case OP_JMP:
                do_JMP(instr);
                break;
            case OP_JSR:
                do_JSR(instr);
                break;
            case OP_LD:
                do_LD(instr);
                break;
            case OP_LDI:
                do_LDI(instr);
                break;
            case OP_LDR:
                do_LDR(instr);
                break;
            case OP_LEA:
                do_LEA(instr);
                break;
            case OP_ST:
                do_ST(instr);
                break;
            case OP_STI:
                do_STI(instr);
                break;
            case OP_STR:
                do_STR(instr);
                break;
            case OP_RET:
                do_RET(instr);
                break;
            case OP_TRAP:
                do_TRAP(instr, running);
                break;
            case OP_RES:
            case OP_RTI:
            default:
                abort();
                break;
        }
    }
    restore_input_buffering();
}
