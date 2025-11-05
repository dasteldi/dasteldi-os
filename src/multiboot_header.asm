section .multiboot

align 4
multiboot_header:
    dd 0x1BADB002
    dd 0x00000003  
    dd -(0x1BADB002 + 0x00000003)

section .text
global _start
extern kernel_main  

_start:
    mov esp, _stack_top
    
    call kernel_main
    
    cli
.hang:
    hlt
    jmp .hang

section .bss
align 16
_stack_bottom:
    resb 16384
_stack_top: