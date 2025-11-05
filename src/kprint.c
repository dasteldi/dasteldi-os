#include "kprint.h"

static unsigned short cursor_pos = 0;

// Очистка экрана
void kprint_clear(void) {
    volatile char *video = (volatile char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = 0x07;
    }
    cursor_pos = 0;
}

// Прокрутка экрана
static void scroll(void) {
    volatile char *video = (volatile char*)0xb8000;
    
    for (int i = 0; i < 80 * 24 * 2; i++) {
        video[i] = video[i + 160];
    }
    
    for (int i = 80 * 24 * 2; i < 80 * 25 * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = 0x07;
    }
}

void kprint(const char *str) {
    volatile char *video = (volatile char*)0xb8000;
    
    while (*str) {
        if (*str == '\n') {
            cursor_pos += 80;
            cursor_pos = (cursor_pos / 80) * 80; // Выравнивание до начала строки
        } 
        else if (*str == '\r') {
            cursor_pos = (cursor_pos / 80) * 80; // Начало текущей строки
        }
        else {
            if (cursor_pos >= 80 * 25) {
                scroll();
                cursor_pos = 80 * 24; 
            }
            
            video[cursor_pos * 2] = *str;
            video[cursor_pos * 2 + 1] = 0x07;
            cursor_pos++;
        }
        
        str++;
    }
}