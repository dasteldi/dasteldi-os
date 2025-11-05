#include "interrupts.h"
#include "kprint.h"


unsigned char inb(unsigned short port) {
    unsigned char result;
    asm volatile ("inb %1, %0" : "=a"(result) : "dN"(port));
    return result;
}

void outb(unsigned short port, unsigned char data) {
    asm volatile ("outb %0, %1" : : "a"(data), "dN"(port));
}


void irq_enable(int irq) {
    unsigned short port;
    unsigned char value;
    
    if (irq < 8) {
        port = 0x21;
    } else {
        port = 0xA1;
        irq -= 8;
    }
    value = inb(port) & ~(1 << irq);
    outb(port, value);
}

void idt_init(void) {
    kprint("IDT: Basic setup\n");
    irq_enable(1);
}