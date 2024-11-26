#ifndef STACK_H_INCLUDED

/// Начало:

#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "../common/common.h"   // включаем общий заголовочный файл

/// Определение структуры стека:
typedef
struct _stack
{
	STACK_DATA_TYPE stack_data; // данные стёка
	size_t allocated;           // выделенная память
	size_t stack_size;          // размер стёка
} Stack;

/// Прототипы функций для работы со стеком:
Stack *create_stack();

void *stack_pop(Stack *);
void free_stack(Stack *);
void *stack_peek(Stack *);
void print_stack(Stack *);
void stack_push(Stack *, void *);

#endif // конец
