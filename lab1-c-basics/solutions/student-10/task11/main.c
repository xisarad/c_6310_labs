 /*
 * Лабораторная работа №1
 * Студент: номер: 10
 * Вариант: 11
 * Задание: 11 Сумма ряда 1 + 1/2 + 1/3 + ... + 1/n
 */

#include <stdio.h>

int main(void) {
    int n;
    double sum = 0.0;
    
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