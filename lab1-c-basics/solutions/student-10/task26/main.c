/*
 * Лабораторная работа №1
 * Студент: номер: 10
 * Вариант: 11
 * Задание: 26 (Проверка строки на панграмму)
 * The quick brown fox jumps over the lazy dog 
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

int is_pangram(const char *str) {
    int letters[ALPHABET_SIZE] = {0};
    int length = strlen(str);
    int count = 0;
    
    for (int i = 0; i < length; ++i) {
        char ch = tolower(str[i]);
        
        if (ch >= 'a' && ch <= 'z') {
            int index = ch - 'a';
            if (!letters[index]) {
                letters[index] = 1;
                ++count;
            }
        }
    }
    
    return (count == ALPHABET_SIZE);
}

int main(void) {
    char input[256];
    
    printf("Pangram checker (English alphabet A-Z)\n");
    printf("Enter a string: ");
    
    if (!fgets(input, sizeof(input), stdin)) {
        printf("Input error.\n");
        return 1;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    if (is_pangram(input)) {
        printf("It IS a pangram!\n");
    } else {
        printf("It is NOT a pangram.\n");
    }
    
    return 0;
}