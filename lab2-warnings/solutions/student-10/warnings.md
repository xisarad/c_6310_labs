# Отчет о предупреждениях

**Студент:** 10  
**Задание:** 11 (Сумма ряда 1 + 1/2 + 1/3 + ... + 1/n)  
**Всего предупреждений:** 15 (10 -Wall, 5 -Wextra)

---

## Предупреждения -Wall (10 разных типов)

### 1. -Wunused-parameter
**Строка:** 17  
**Код:** `static void func_unused_param(int unused)`  
**Текст:** `warning: unused parameter 'unused' [-Wunused-parameter]`  
**Объяснение:** Параметр функции объявлен, но не используется.

### 2. -Wunused-function
**Строка:** 22  
**Код:** `static void unused_function(void)`  
**Текст:** `warning: 'unused_function' defined but not used [-Wunused-function]`  
**Объяснение:** Статическая функция определена, но не вызывается.

### 3. -Wunused-variable
**Строка:** 28  
**Код:** `int unused_x = 100;`  
**Текст:** `warning: unused variable 'unused_x' [-Wunused-variable]`  
**Объяснение:** Переменная объявлена и инициализирована, но не используется.

### 4. -Wuninitialized
**Строка:** 34  
**Код:** `int x; return x;`  
**Текст:** `warning: 'x' is used uninitialized [-Wuninitialized]`  
**Объяснение:** Использование переменной до её инициализации.

### 5. -Wreturn-type
**Строка:** 40  
**Код:** `int no_return_demo(void) { ... }` (нет return)  
**Текст:** `warning: control reaches end of non-void function [-Wreturn-type]`  
**Объяснение:** Функция объявлена как возвращающая int, но не содержит return.

### 6. -Wsign-compare
**Строка:** 46  
**Код:** `if (a < b)` где `int a` и `unsigned int b`  
**Текст:** `warning: comparison of integer expressions of different signedness [-Wsign-compare]`  
**Объяснение:** Сравнение знакового и беззнакового типа.

### 7. -Wparentheses
**Строка:** 50  
**Код:** `if (a = b)`  
**Текст:** `warning: suggest parentheses around assignment used as truth value [-Wparentheses]`  
**Объяснение:** Присваивание внутри условия — возможная опечатка.

### 8. -Wempty-body
**Строка:** 56  
**Код:** `if (x > 0);`  
**Текст:** `warning: suggest braces around empty body in an 'if' statement [-Wempty-body]`  
**Объяснение:** Точка с запятой создает пустое тело условного оператора.

### 9. -Wchar-subscripts
**Строка:** 62  
**Код:** `return arr[c];` где `char c`  
**Текст:** `warning: array subscript has type 'char' [-Wchar-subscripts]`  
**Объяснение:** Использование char как индекса массива.

### 10. -Wswitch-enum
**Строка:** 69  
**Код:** `switch (color) { case RED: break; }`  
**Текст:** `warning: enumeration value 'GREEN' not handled in switch [-Wswitch-enum]`  
**Объяснение:** В операторе switch обработаны не все значения перечисления.

---

## Предупреждения -Wextra (бонус, 5 разных типов)

### 1. -Wunused-but-set-variable
**Строка:** 86  
**Код:** `int value = 42;`  
**Текст:** `warning: variable 'value' set but not used [-Wunused-but-set-variable]`  
**Объяснение:** Переменной присвоено значение, которое никогда не используется.

### 2. -Wtype-limits
**Строка:** 92  
**Код:** `if (x >= 0)` где `unsigned int x`  
**Текст:** `warning: comparison of unsigned expression in '>= 0' is always true [-Wtype-limits]`  
**Объяснение:** Для беззнаковых типов сравнение с >= 0 всегда истинно.

### 3. -Wmissing-field-initializers
**Строка:** 103  
**Код:** `struct Point p = {1, 2};`  
**Текст:** `warning: missing initializer for field 'z' of 'struct Point' [-Wmissing-field-initializers]`  
**Объяснение:** Не все поля структуры явно инициализированы.

### 4. -Woverflow
**Строка:** 109  
**Код:** `int x = 2147483647 + 1;`  
**Текст:** `warning: integer overflow in expression of type 'int' [-Woverflow]`  
**Объяснение:** Константное выражение вызывает переполнение целого типа.

### 5. -Wunused-but-set-parameter
**Строка:** 115  
**Код:** `static void unused_but_set_param(int value) { value = 42; }`  
**Текст:** `warning: parameter 'value' set but not used [-Wunused-but-set-parameter]`  
**Объяснение:** Параметру присваивается значение, которое затем не используется.

---

## Проверка

### Компиляция с -Wall
gcc -std=c99 -Wall main.c -o program
Результат: 10 предупреждений (разных типов)

### Компиляция с -Wall -Wextra
gcc -std=c99 -Wall -Wextra main.c -o program
Результат: 15 предупреждений (10 -Wall + 5 -Wextra)

## Запуск программы
./program
Enter a positive integer n: 5
Sum for n = 5 is: 2.2833333333