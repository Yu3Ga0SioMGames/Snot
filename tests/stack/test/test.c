#include "test.h"

int stack_test()
{
	Stack *stack;
	stack = NULL;

	printf("%p\n", stack_pop(stack));
	printf("\n%p\n\n", stack_peek(stack));

	stack = create_stack();
	int64_t initial_size = 10;

	int64_t value = 1;
	stack_push(stack, &value);
	printf("%ld\n", *(int64_t *)stack_peek(stack));
	printf("\n%ld\n", *(int64_t *)stack_pop(stack));
	printf("\n%p\n\n", stack_peek(stack));

	for(int64_t i = 0; i < initial_size; ++i) {
		stack_push(stack, &i);
	}

	int64_t extra_value = 87;
	stack_push(stack, &extra_value);
	print_stack(stack);
	printf("\n%ld\n\n", *(int64_t *)stack_pop(stack));
	print_stack(stack);
	printf("\n%ld\n\n", *(int64_t *)stack_peek(stack));

	free_stack(stack);
	return 0;
}
