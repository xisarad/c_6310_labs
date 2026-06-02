/*
 * Лабораторная работа №2
 * Студент: номер: 10
 * Вариант: 11
 * Задание: 11 (Сумма ряда 1 + 1/2 + 1/3 + ... + 1/n)
 * Количество предупреждений: 15 (10 -Wall, 5 -Wextra)
 */

#include <stdio.h>
#include <setjmp.h>




/* ========== ПРЕДУПРЕЖДЕНИЯ -Wall ========== */

/* WARNING 1: -Wunused-parameter */
static void func_unused_param(int unused) {
    // параметр не используется — предупреждение появится
}

/* WARNING 2: -Wunused-function */
static void unused_function(void) {
    // эта функция никогда не вызывается
}

/* WARNING 3: -Wunused-variable */
void unused_var_demo(void) {
    int unused_x = 100;  // объявлена, но не используется
}

/* WARNING 4: -Wuninitialized */
int uninitialized_demo(void) {
    int x;           // не инициализирована
    return x;        // используется без инициализации
}

/* WARNING 5: -Wreturn-type */
int no_return_demo(void) {
    printf("No return here\n");
    // нет оператора return
}

/* WARNING 6: -Wsign-compare */
int sign_compare_demo(int a, unsigned int b) {
    if (a < b) return 1;  // сравнение signed и unsigned
    return 0;
}

/* WARNING 7: -Wparentheses */
int parentheses_demo(int a, int b) {
    if (a = b) return 1;  // присваивание вместо сравнения
    return 0;
}

/* WARNING 8: -Wempty-body */
void empty_body_demo(int x) {
    if (x > 0);           // точка с запятой = пустое тело
    printf("x > 0?\n");
}

/* WARNING 9: -Wchar-subscripts */
int char_subscript_demo(void) {
    int arr[10] = {0,1,2,3,4,5,6,7,8,9};
    char c = '5';
    return arr[c];        // char используется как индекс
}

/* WARNING 10: -Wswitch-enum */
enum Colors { RED, GREEN, BLUE };
void switch_enum_demo(enum Colors color) {
    switch (color) {
        case RED:
            break;
        // GREEN и BLUE не обработаны
    }
}




/* ========== ПРЕДУПРЕЖДЕНИЯ -Wextra (бонус) ========== */

/* WARNING 11: -Wunused-but-set-variable */
void unused_but_set_demo(void) {
    int value = 42;       // присвоили, но не использовали
}

/* WARNING 12: -Wtype-limits */
unsigned int type_limits_demo(void) {
    unsigned int x = 5;
    if (x >= 0) return x;  // unsigned всегда >= 0
    return 0;
}

/* WARNING 13: -Wmissing-field-initializers */
struct Point {
    int x, y, z;
};

void missing_init_demo(void) {
    struct Point p = {1, 2};  // пропущена инициализация поля z
    (void)p;
}

/* WARNING 14: -Woverflow */
int overflow_demo(void) {
    int x = 2147483647 + 1;   // переполнение int
    return x;
}

/* WARNING 15: -Wunused-but-set-parameter */
static void unused_but_set_param(int value) {
    value = 42;  // присвоили, но не использовали
}


/* ========== ОСНОВНАЯ ПРОГРАММА ========== */

int main(void) {
    int n;
    double sum = 0.0;
    
    /* ВЫЗОВЫ ФУНКЦИЙ ДЛЯ ГЕНЕРАЦИИ ПРЕДУПРЕЖДЕНИЙ */
    func_unused_param(10);
    unused_var_demo();
    uninitialized_demo();
    no_return_demo();
    sign_compare_demo(5, 10);
    parentheses_demo(1, 2);
    empty_body_demo(5);
    char_subscript_demo();
    switch_enum_demo(RED);
    unused_but_set_demo();
    type_limits_demo();
    missing_init_demo();
    overflow_demo();
    unused_but_set_param(100);
    
    /* ОСНОВНАЯ ЛОГИКА ЗАДАНИЯ (СУММА РЯДА) */
    printf("Sum of series: 1 + 1/2 + 1/3 + ... + 1/n\n");
    printf("Enter a positive integer n: ");
     
    if (scanf("%d", &n) != 1) {
        printf("Error: invalid input. Please enter an integer.\n");
        return 1;
    }
    
    if (n <= 0) {
        printf("Error: n must be a positive integer (n > 0).\n");
        return 1;
    }
    
    for (int i = 1; i <= n; ++i) {
        sum += 1.0 / i;
    }
    
    printf("Sum for n = %d is: %.10f\n", n, sum);
    
    return 0;
}