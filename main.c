#include "reader/reader.h"                                                     // подключаем заголовочный файл

int main(int argcount, char *argvalues[])
{
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
		}
	}

	if(incomplete_expression != NULL) {
		free_expression(incomplete_expression);                                // освобождаем память, выделенную под незавершенное выражение
	}

	printf("\n");

	return 0;                                                                  // завершаем выполнение
}
