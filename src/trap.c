#include <stdio.h>
#include <stdint.h>
#include "lc3.h"

void trap_put(uint16_t reg[]) {
    /* one char per word */
    uint16_t* c = memory + reg[R_R0];
    while (*c) {
        putc((char)*c, stdout);
        c++;
    }
    fflush(stdout);
}

void trap_getc(uint16_t reg[]) {
    /* read a single ASCII char */
    reg[R_R0] = (uint16_t)getchar();
    update_flags(R_R0);
}

void trap_out(uint16_t reg[]) {
    putc((char)reg[R_R0], stdout);
    fflush(stdout);
}

void trap_in(uint16_t reg[]) {
    printf("Enter a character: ");
    char c = getchar();
    putc(c, stdout);
    fflush(stdout);
    reg[R_R0] = (uint16_t)c;
    update_flags(R_R0);
}

void trap_put(uint16_t reg[]) {
    /* one char per byte (two bytes per word) here we need to swap back to big endian format */
    uint16_t* c = memory + reg[R_R0];
    while (*c)
    {
        char char1 = (*c) & 0xFF;
        putc(char1, stdout);
        char char2 = (*c) >> 8;
        if (char2) putc(char2, stdout);
        ++c;
    }
    fflush(stdout);
}

void trap_halt(int running) {
    puts("HALT");
    fflush(stdout);
    running = 0;
}
