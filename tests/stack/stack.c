#include "stack.h"

bool expand_allocated_memory(Stack *stack)
{
	if(stack == NULL) {
		container_error = CONTAINER_NOT_PROVIDED;
		return false;
	}

	size_t new_size = stack->allocated * 2;
	STACK_DATA_TYPE new_memory = malloc(sizeof(void *) * new_size);
	if(new_memory == NULL) {
		container_error = BAD_ALLOC_ERROR;
		return false;
	}

	for(size_t i = 0; i < stack->stack_size; ++i) {
		((void **)new_memory)[i] = ((void **)stack->stack_data)[i];
	}

	free(stack->stack_data);

	stack->stack_data = new_memory;
	stack->allocated = new_size;

	return true;
}

Stack *create_stack()
{
	Stack *new_stack = (Stack *)malloc(sizeof(Stack));
	if(new_stack == NULL) {
		container_error = BAD_ALLOC_ERROR;
		return NULL;
	}

	new_stack->stack_data = malloc(sizeof(void *));
	if(new_stack->stack_data == NULL) {
		container_error = BAD_ALLOC_ERROR;
		free(new_stack);
		return NULL;
	}
	new_stack->allocated = 1;
	new_stack->stack_size = 0;

	return new_stack;
}

void free_stack(Stack *stack)
{
	if(stack == NULL) {
		container_error = CONTAINER_NOT_PROVIDED;
		return;
	}

	free(stack->stack_data);
	free(stack);
}

void print_stack(Stack *stack)
{
	if(stack == NULL) {
		container_error = CONTAINER_NOT_PROVIDED;
		return;
	}

	if(stack->stack_size == 0) {
		container_error = CONTAINER_IS_EMPTY;
		return;
	}

	for(size_t i = 0; i < stack->stack_size; ++i) {
		printf("%ld ", *(int64_t *)((void **)stack->stack_data)[i]);
	}
	printf("\n");
}

void stack_push(Stack *stack, void *value)
{
	if(stack == NULL) {
		container_error = CONTAINER_NOT_PROVIDED;
		return;
	}

	if(stack->stack_size == stack->allocated) {
		if(!expand_allocated_memory(stack)) {
			container_error = BAD_ALLOC_ERROR;
			return;
		}
	}

	((void **)stack->stack_data)[stack->stack_size] = value;
	stack->stack_size++;
}

void *stack_pop(Stack *stack)
{
	if(stack == NULL) {
		container_error = CONTAINER_NOT_PROVIDED;
		return NULL;
	}

	if(stack->stack_size == 0) {
		container_error = CONTAINER_IS_EMPTY;
		return NULL;
	}

	return ((void **)stack->stack_data)[--stack->stack_size];
}

void *stack_peek(Stack *stack)
{
	if(stack == NULL) {
		container_error = CONTAINER_NOT_PROVIDED;
		return NULL;
	}

	if(stack->stack_size == 0) {
		container_error = CONTAINER_IS_EMPTY;
		return NULL;
	}

	return ((void **)stack->stack_data)[stack->stack_size - 1];
}
