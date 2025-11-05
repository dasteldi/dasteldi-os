#include "keyboard.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64


void keyboard_handler(void) {
    // Пустая заглушка
}


static unsigned char inb(unsigned short port) {
    unsigned char result;
    asm volatile ("inb %1, %0" : "=a"(result) : "dN"(port));
    return result;
}

static const char scancode_to_ascii[128] = {
    0,  0,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
    0,  '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0,  ' '
};

void keyboard_init(void) {
    // Пустая инициализация
}

char keyboard_getc(void) {
    unsigned char status = inb(KEYBOARD_STATUS_PORT);
    
    if (status & 0x01) { 
        unsigned char scancode = inb(KEYBOARD_DATA_PORT);
        
        if (!(scancode & 0x80)) {
            if (scancode < sizeof(scancode_to_ascii)) {
                char c = scancode_to_ascii[scancode];
                if (c != 0) {
                    return c;
                }
            }
        }
    }
    
    return 0; 
}