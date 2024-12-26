#include "reader.h"

const char empty[] = "";

List *scan(FILE *in)
{
    char *str = input(in);
    str_split_str();
}

/// Один из этапов создания Своего Языка Программирования:
Expression *reader(Expression *incomplete_expression, char *file_path)
{
	char *str = input();

	if(str == NULL || strlen(str) == 0) {                         // проверка на окончание ввода или пустую строку
		if(feof(stdin)) {
			return NULL;
		}

		if(incomplete_expression != NULL) {
			return incomplete_expression;
		} else {
			incomplete_expression = create_expression();

			incomplete_expression->is_complete = true;

			return incomplete_expression;
		}
	}

	size_t num_tokens = 0;                                        // переменная для хранения количества токенов

	char **tokens = str_split_str(str, &num_tokens);              // разбиваем строку "str" на токены и сохраняем их в массив "tokens"
	if(tokens == NULL) {                                          // если разбиение строки не удалось, возвращаем ошибку
		printf("Error Splitting Tokens!!!\n");

		return incomplete_expression;
	}

	str_print_tokens(tokens, num_tokens);                         // печатаем токены, находящиеся в массиве "tokens"

	size_t num_of_converted_tokens = 0;                           // переменная для хранения количества преобразованных токенов

	/// Преобразуем токены:
	Token **converted_tokens = str_convert_tokens((const char **)tokens, num_tokens, &num_of_converted_tokens);
	if(converted_tokens == NULL) {                                // проверяем, удалось ли выделить память и преобразовать токены
		printf("Error Converting Tokens!!!\n\n");

		str_free_tokens(tokens, num_tokens);                      // освобождаем память, выделенную под токены в массиве
		return incomplete_expression;
	}

	str_print_tokens2(converted_tokens, num_of_converted_tokens); // выводим преобразованные токены

	/// Разбираем токены в выражение:
	Expression *parsed_expression = parse(converted_tokens, num_of_converted_tokens, incomplete_expression);
	if(parsed_expression != NULL) {
		if(parsed_expression->is_complete) {
			long long depth = 1;
			print_expression(parsed_expression, depth, NULL);

			incomplete_expression = NULL;                         // сбрасываем указатель на незавершенное выражение
		}

		incomplete_expression = parsed_expression;                // сохраняем незавершенное выражение
	}

	str_free_str(str);
	str_free_tokens(tokens, num_tokens);                          // освобождаем память, выделенную под токены в массиве
	str_free_tokens2(converted_tokens, num_of_converted_tokens);  // освобождаем память, выделенную под преобразованные токены в массиве
	return incomplete_expression;                                 // возвращаем незавершенное выражение
}
