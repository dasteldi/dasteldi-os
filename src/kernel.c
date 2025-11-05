#include "kprint.h"
#include "keyboard.h"
#include "shell.h"

void kernel_main(void) {
    kprint_clear();
    kprint("Welcome to Dasteldi OS!\n");
    kprint("Type 'help' for commands\n");
    
    keyboard_init();
    
    // Запускаем командную строку
    shell_run();
    
    // Сюда не должны дойти
    while (1) {
        asm volatile ("hlt");
    }
}