section .text

global keyboard_handler_asm
extern keyboard_handler

keyboard_handler_asm:
    pushad
    call keyboard_handler
    ; Отправляем EOI (End Of Interrupt)
    mov al, 0x20
    out 0x20, al
    popad
    iretd