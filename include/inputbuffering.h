#ifndef INPUT_BUFFERING_WINDOWS
#define INPUT_BUFFERING_WINDOWS

/* Supported only in Windows */

#include <stdint.h>

void disable_input_buffering();
void restore_input_buffering();
uint16_t check_key();

#endif