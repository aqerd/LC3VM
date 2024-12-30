#ifndef INPUT_BUFFERING_UNIX
#define INPUT_BUFFERING_UNIX

#include <stdint.h>

void disable_input_buffering();
void restore_input_buffering();
uint16_t check_key();

#endif