#ifndef TRAP
#define TRAP

void trap_put(uint16_t reg[]);
void trap_getc(uint16_t reg[]);
void trap_out(uint16_t reg[]);
void trap_in(uint16_t reg[]);
void trap_halt(int running);

#endif