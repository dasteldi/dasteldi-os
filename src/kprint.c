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
    
    // Копируем все строки на одну вверх
    for (int i = 0; i < 80 * 24 * 2; i++) {
        video[i] = video[i + 160];
    }
    
    // Очищаем последнюю строку
    for (int i = 80 * 24 * 2; i < 80 * 25 * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = 0x07;
    }
}

// Основная функция вывода
void kprint(const char *str) {
    volatile char *video = (volatile char*)0xb8000;
    
    while (*str) {
        // Обработка перевода строки
        if (*str == '\n') {
            cursor_pos += 80;
            cursor_pos = (cursor_pos / 80) * 80; // Выравнивание до начала строки
        } 
        // Обработка возврата каретки
        else if (*str == '\r') {
            cursor_pos = (cursor_pos / 80) * 80; // Начало текущей строки
        }
        // Обычный символ
        else {
            // Проверяем, не вышли ли за пределы экрана
            if (cursor_pos >= 80 * 25) {
                scroll();
                cursor_pos = 80 * 24; // Последняя строка
            }
            
            // Выводим символ
            video[cursor_pos * 2] = *str;
            video[cursor_pos * 2 + 1] = 0x07;
            cursor_pos++;
        }
        
        str++;
    }
}