#ifndef LITTLE_COMPUTER_MEMORY
#define LITTLE_COMPUTER_MEMORY

#include <stdint.h>

enum {
    MR_KBSR = 0xFE00, /* keyboard status */
    MR_KBDR = 0xFE02  /* keyboard data */
};

void mem_write(uint16_t address, uint16_t val);
uint16_t mem_read(uint16_t address);

#endif