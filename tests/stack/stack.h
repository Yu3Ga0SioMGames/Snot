#ifndef STACK_H_INCLUDED

#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "../common/common.h"

typedef
struct _stack
{
	STACK_DATA_TYPE stack_data;
	size_t allocated;
	size_t stack_size;
} Stack;

Stack *create_stack();

void *stack_pop(Stack *);
void free_stack(Stack *);
void *stack_peek(Stack *);
void print_stack(Stack *);
void stack_push(Stack *, void *);

#endif
