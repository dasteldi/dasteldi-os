#ifndef INTERRUPTS_H
#define INTERRUPTS_H

unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char data);

void idt_init(void);
void irq_enable(int irq);

#endif