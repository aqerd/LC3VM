#include <stdio.h>
#include <signal.h>
#include "lc3.h"
#include "utils.h"

void load_arguments(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int j = 1; j < argc; ++j) {
        if (!read_image(argv[j])) {
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }
}

int main(int argc, const char* argv[]) {
    load_arguments(argc, argv);
    
    signal(SIGINT, handle_interrupt(1));
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
                do_ADD(instr, op);
                break;
            case OP_AND:
                do_AND(instr, op);
                break;
            case OP_NOT:
                do_NOT(instr, op);
                break;
            case OP_BR:
                do_BR(instr, op);
                break;
            case OP_JMP:
                do_JMP(instr, op);
                break;
            case OP_JSR:
                do_JSR(instr, op);
                break;
            case OP_LD:
                do_LD(instr, op);
                break;
            case OP_LDI:
                do_LDI(instr, op);
                break;
            case OP_LDR:
                do_LDR(instr, op);
                break;
            case OP_LEA:
                do_LEA(instr, op);
                break;
            case OP_ST:
                do_ST(instr, op);
                break;
            case OP_STI:
                do_STI(instr, op);
                break;
            case OP_STR:
                do_STR(instr, op);
                break;
            case OP_TRAP:
                do_TRAP(instr, op);
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
