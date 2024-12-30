#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>

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