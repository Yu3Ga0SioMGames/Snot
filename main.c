#include "reader/reader.h"                                                     // подключаем заголовочный файл

#include "libmap/map.h"
#include "printer/printer.h"
#include "evaluator/evaluator.h"

#define PROMPT_COMPLETE ">>>"
#define PROMPT_INCOMPLETE ">.."

void repl(FILE *in, FILE *out, FILE *err);

void print_prompt(bool complete);

int main(int argcount, char *argvalues[])
{
	variables = map_create();
	if(variables == NULL) {
		printf("Error: Unable To Initialize Map!!!\n\n");

		return 0;
	}

	Expression *incomplete_expression = NULL;                                  // указатель для хранения незавершенного выражения

	if(argcount > 1) {                                                         // проверяем, передан ли путь к файлу в аргументах
		char *file_path = argvalues[1];                                        // получаем путь к файлу из аргументов

		char *file_content = str_read_file(file_path);                         // читаем содержимое файла
		if(file_content == NULL) {
			printf("Error!!! Reading File Or Empty Path: %s!!!\n\n", file_path);

			return 0;                                                          // завершаем программу, если не удалось прочитать файл
		}

		incomplete_expression = reader(NULL, file_content);                    // передаем содержимое файла в reader
	}

	while(1) {                                                                 // бесконечный цикл для повторного выполнения
		if(incomplete_expression != NULL && incomplete_expression->is_complete == false) {
			printf(">..");                                                     // печатаем ">.", если выражение не завершено
		} else {
			printf(">>>");
		}

		Expression *result_expression = reader(incomplete_expression, NULL);   // анализируем объединенную строку

		if(result_expression == NULL) {
			break;
		} else if(!(result_expression->is_complete)) {
			incomplete_expression = result_expression;
		} else if(list_length(result_expression->element_list) == 0) {
			free_expression(result_expression);
			incomplete_expression = NULL;
		} else {
			for(size_t i = 0; i < result_expression->element_list->length; ++i) {
				ExpressionElement *current = NULL;
				int rc = get_from_list(result_expression->element_list, i, &current);
				if(rc != 0) {
					rc = 0;
				}

				Value *result = eval(current);
				if(result != NULL) {
					print_value(result);

					/// free_value(result);
				} else {
					printf("No Result Or Invalid Expression!!!\n\n");
				}
			}
		}
	}

	if(incomplete_expression != NULL) {
		free_expression(incomplete_expression);                                // освобождаем память, выделенную под незавершенное выражение
	}

	map_destroy(variables);                                                    // освобождаем память, выделенную под карту переменных

	printf("\n");

	return 0;                                                                  // завершаем выполнение
}

void repl(FILE *input, FILE *output, FILE *error)
{
    bool expr_complete = true;

    while(has_no_input(input))
    {
        print_prompt(expr_complete);

        Expression *expr = read(input);
        expr_complete = expr->is_complete;

        Value *value = eval(expr);

        print(value);
    }
}

void print_prompt(bool complete)
{
    if(complete) {
        printf(PROMPT_COMPLETE);
    } else {
        printf(PROMPT_INCOMPLETE);
    }
}

Expression *read(FILE *input)
{
    List *tokens = scan(input);
    Expression *expr = parse(tokens);
    free_list(tokens);

    return expr;
}

List *scan(FILE *input)
{

}
