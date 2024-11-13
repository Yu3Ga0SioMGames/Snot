#include "test.h"

int test_parser()
{
	/// Пример использования с массивом токенов:
	Token tokens[] = {
		{'(', NULL},
		{'[', NULL},
		{'(', NULL},
		{')', NULL},
		{']', NULL},
		{'}', NULL}
	};
	size_t token_count = sizeof(tokens) / sizeof(tokens[0]);

	/// Преобразуем массив в массив указателей на токены:
	Token *token_ptrs[token_count];
	for(size_t i = 0; i < token_count; ++i) {
		token_ptrs[i] = &tokens[i];
	}

	Expression *parsed_expression = parse(token_ptrs, token_count);
	if(parsed_expression != NULL) {
		printf("Разбор выражения успешен.\n");
	} else {
		printf("Ошибка при разборе выражения.\n");
	}

	/// Освобождаем память:
	free_expression(parsed_expression);

	return 0;
}
