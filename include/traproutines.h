#ifndef TRAP_ROUTINES
#define TRAP_ROUTINES

void trap_puts(uint16_t reg[]);
void trap_getc(uint16_t reg[]);
void trap_putsp(uint16_t reg[]);
void trap_out(uint16_t reg[]);
void trap_in(uint16_t reg[]);
void trap_halt(int running);

#endif