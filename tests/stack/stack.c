#include "stack.h"                                                  // включаем заголовочный файл

/// Функция расширения выделенной памяти для стека:
bool expand_allocated_memory(Stack *stack)
{
	if(stack == NULL) {                                             // проверяем, не является ли стек "NULL"
		container_error = CONTAINER_NOT_PROVIDED;
		return false;
	}

	size_t new_size = stack->allocated * 2;                         // рассчитываем новый размер памяти
	STACK_DATA_TYPE new_memory = malloc(sizeof(void *) * new_size); // выделяем новую память
	if(new_memory == NULL) {                                        // проверяем, успешно ли выделена новая память
		container_error = BAD_ALLOC_ERROR;
		return false;
	}

	for(size_t i = 0; i < stack->stack_size; ++i) {                 // копируем данные в новую память
		((void **)new_memory)[i] = ((void **)stack->stack_data)[i];
	}

	free(stack->stack_data);                                        // освобождаем старую память

	stack->stack_data = new_memory;                                 // присваиваем новую память стеку
	stack->allocated = new_size;                                    // обновляем размер выделенной памяти

	return true;
}

/// Функция создания нового стека:
Stack *create_stack()
{
	Stack *new_stack = (Stack *)malloc(sizeof(Stack));              // выделяем память для нового стека
	if(new_stack == NULL) {                                         // проверяем, успешно ли выделена память
		container_error = BAD_ALLOC_ERROR;
		return NULL;
	}

	new_stack->stack_data = malloc(sizeof(void *));                 // выделяем память для данных стека
	if(new_stack->stack_data == NULL) {                             // проверяем, успешно ли выделена память для данных
		container_error = BAD_ALLOC_ERROR;
		free(new_stack);
		return NULL;
	}
	new_stack->allocated = 1;                                       // инициализируем размер выделенной памяти
	new_stack->stack_size = 0;                                      // инициализируем размер стека

	return new_stack;
}

/// Функция освобождения памяти стека:
void free_stack(Stack *stack)
{
	if(stack == NULL) {                                             // проверяем, не является ли стек "NULL"
		container_error = CONTAINER_NOT_PROVIDED;
		return;
	}

	free(stack->stack_data);                                        // освобождаем память данных стека
	free(stack);                                                    // освобождаем память самого стека
}

/// Функция печати элементов стека:
void print_stack(Stack *stack)
{
	if(stack == NULL) {                                             // проверяем, не является ли стек "NULL"
		container_error = CONTAINER_NOT_PROVIDED;
		return;
	}

	if(stack->stack_size == 0) {                                    // проверяем, не является ли стек пустым
		container_error = CONTAINER_IS_EMPTY;
		return;
	}

	for(size_t i = 0; i < stack->stack_size; ++i) {                 // печатаем каждый элемент стека
		printf("%ld ", *(int64_t *)((void **)stack->stack_data)[i]);
	}
	printf("\n");                                                   // добавляем перевод строки после печати стека
}

/// Функция добавления элемента в стек:
void stack_push(Stack *stack, void *value)
{
	if(stack == NULL) {                                             // проверяем, не является ли стек "NULL"
		container_error = CONTAINER_NOT_PROVIDED;
		return;
	}

	if(stack->stack_size == stack->allocated) {                     // проверяем, нужно ли расширение памяти
		if(!expand_allocated_memory(stack)) {                       // если нужно, расширяем память
			container_error = BAD_ALLOC_ERROR;
			return;
		}
	}

	((void **)stack->stack_data)[stack->stack_size] = value;        // добавляем новый элемент в стек
	stack->stack_size++;                                            // увеличиваем размер стека
}

/// Функция извлечения элемента из стека:
void *stack_pop(Stack *stack)
{
	if(stack == NULL) {                                             // проверяем, не является ли стек "NULL"
		container_error = CONTAINER_NOT_PROVIDED;
		return NULL;
	}

	if(stack->stack_size == 0) {                                    // проверяем, не является ли стек пустым
		container_error = CONTAINER_IS_EMPTY;
		return NULL;
	}

	return ((void **)stack->stack_data)[--stack->stack_size];       // возвращаем последний элемент стека и уменьшаем его размер
}

/// Функция просмотра верхнего элемента стека:
void *stack_peek(Stack *stack)
{
	if(stack == NULL) {                                             // проверяем, не является ли стек "NULL"
		container_error = CONTAINER_NOT_PROVIDED;
		return NULL;
	}

	if(stack->stack_size == 0) {                                    // проверяем, не является ли стек пустым
		container_error = CONTAINER_IS_EMPTY;
		return NULL;
	}

	return ((void **)stack->stack_data)[stack->stack_size - 1];     // возвращаем верхний элемент стека без изменения его размера
}
