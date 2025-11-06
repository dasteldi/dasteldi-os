#include "kprint.h"

static unsigned short cursor_pos = 0;
static unsigned char current_color = 0x07; // По умолчанию: светло-серый на черном

// Установка цвета текста и фона
void kprint_set_color(unsigned char foreground, unsigned char background) {
    current_color = (background << 4) | (foreground & 0x0F);
}

// Очистка экрана текущим цветом
void kprint_clear(void) {
    volatile char *video = (volatile char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = current_color;
    }
    cursor_pos = 0;
}

// Прокрутка экрана
static void scroll(void) {
    volatile char *video = (volatile char*)0xb8000;
    
    // Копируем строки 1-24 в строки 0-23
    for (int i = 0; i < 80 * 24 * 2; i++) {
        video[i] = video[i + 160];
    }
    
    // Очищаем последнюю строку текущим цветом
    for (int i = 80 * 24 * 2; i < 80 * 25 * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = current_color;
    }
}

// Основная функция вывода
void kprint(const char *str) {
    volatile char *video = (volatile char*)0xb8000;
    
    while (*str) {
        if (*str == '\n') {
            // Переход на новую строку
            cursor_pos += 80;
            cursor_pos = (cursor_pos / 80) * 80;
        } else {
            // Обычный символ
            if (cursor_pos < 80 * 25) {
                video[cursor_pos * 2] = *str;
                video[cursor_pos * 2 + 1] = current_color;
                cursor_pos++;
            }
        }
        
        // Прокрутка при заполнении экрана
        if (cursor_pos >= 80 * 25) {
            scroll();
            cursor_pos = 80 * 24;
        }
        
        str++;
    }
}