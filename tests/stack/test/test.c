#include "test.h"

int stack_test()                                        // тестовая функция для работы со стеком
{
	Stack *stack;                                       // объявляем указатель на стек
	stack = NULL;                                       // инициализируем стек как "NULL"

	printf("%p\n", stack_pop(stack));                   // пытаемся извлечь элемент из пустого стека
	printf("\n%p\n\n", stack_peek(stack));              // пытаемся просмотреть верхний элемент пустого стека

	stack = create_stack();                             // создаем новый стек
	int64_t initial_size = 10;                          // задаем начальный размер стека

	int64_t value = 1;                                  // создаем переменную для добавления в стек
	stack_push(stack, &value);                          // добавляем значение в стек
	printf("%ld\n", *(int64_t *)stack_peek(stack));     // выводим верхний элемент стека
	printf("\n%ld\n", *(int64_t *)stack_pop(stack));    // извлекаем верхний элемент из стека
	printf("\n%p\n\n", stack_peek(stack));              // пытаемся просмотреть верхний элемент пустого стека

	for(int64_t i = 0; i < initial_size; ++i) {         // добавляем несколько элементов в стек
		stack_push(stack, &i);
	}

	int64_t extra_value = 87;                           // добавляем дополнительное значение в стек
	stack_push(stack, &extra_value);
	print_stack(stack);                                 // выводим содержимое стека
	printf("\n%ld\n\n", *(int64_t *)stack_pop(stack));  // извлекаем верхний элемент из стека
	print_stack(stack);                                 // выводим содержимое стека
	printf("\n%ld\n\n", *(int64_t *)stack_peek(stack)); // выводим верхний элемент стека

	free_stack(stack);                                  // освобождаем память, выделенную под стек
	return 0;                                           // возвращаем '0', если все прошло успешно
}
