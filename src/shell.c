#include "shell.h"
#include "kprint.h"
#include "keyboard.h"

void shell_run(void) {
    char input[100];
    int pos = 0;
    
    kprint("\nDasteldi OS> ");
    
    while (1) {
        char c = keyboard_getc();
        
        if (c != 0) {
            if (c == '\n' || c == '\r') {
                kprint("\n");
                input[pos] = '\0';
                if (pos > 0) {
                    if (input[0] == 'h' && input[1] == 'e' && input[2] == 'l' && input[3] == 'p' && input[4] == '\0') {
                        kprint("Commands: help, clear, echo, info\n");
                    }
                    else if (input[0] == 'c' && input[1] == 'l' && input[2] == 'e' && input[3] == 'a' && input[4] == 'r' && input[5] == '\0') {
                        kprint_clear();
                    }
                    else if (input[0] == 'i' && input[1] == 'n' && input[2] == 'f' && input[3] == 'o' && input[4] == '\0') {
                        kprint("Dasteldi OS v1.2 - Simple Operating System\n");
                    }
                    else if (input[0] == 'e' && input[1] == 'c' && input[2] == 'h' && input[3] == 'o' && input[4] == ' ') {
                        kprint(input + 5);
                        kprint("\n");
                    }
                    else {
                        kprint("Unknown command: ");
                        kprint(input);
                        kprint("\n");
                    }
                }
                
                pos = 0;
                kprint("Dasteldi> ");
            }
            else if (c == '\b') {
                if (pos > 0) {
                    pos--;
                    kprint("\b \b");
                }
            }
            else if (c == 27) {
                while (pos > 0) {
                    pos--;
                    kprint("\b \b");
                }
            }
            else {
                if (pos < 99 && c >= 32 && c <= 126) {
                    input[pos] = c;
                    pos++;
                    char str[2] = {c, '\0'};
                    kprint(str);
                }
            }
        }
        
        for (volatile int i = 0; i < 10000; i++);
    }
}