#include "kprint.h"

// Переименовываем _start в kernel_main
void kernel_main(void) {
    kprint("Welcome to Dasteldi OS\n");
    kprint("Author: Dasteldi\n");
    kprint('Write "help" for the command list\n');

    while (1) {
        asm volatile ("hlt");
    }
}