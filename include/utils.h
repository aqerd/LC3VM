#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdint.h>

uint16_t sign_extend(uint16_t x, int bit_count);
void handle_interrupt(int signal);
void update_flags(uint16_t r);
void read_image_file(FILE* file);
uint16_t swap16(uint16_t x);
int read_image(const char* image_path);

#endif