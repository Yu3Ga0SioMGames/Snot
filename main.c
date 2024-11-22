#include "reader/reader.h"                                                     // подключаем заголовочный файл

int main(int argcount, char *argvalues[])
{
	Expression *incomplete_expression = NULL;                                  // указатель для хранения незавершенного выражения

	char *combined_input = NULL;                                               // строка для объединения всех вводов

	while(1) {                                                                 // бесконечный цикл для повторного выполнения
		if(incomplete_expression != NULL && incomplete_expression->is_complete == false) {
			printf(">..");                                                     // печатаем ">>", если выражение не завершено
		} else {
			printf(">>>");
		}



		/*/// Проверяем, начинается ли строка с "snot ":
		if(strncmp(str, "snot ", 5) == 0) {
			char file_path[FILE_SIZE];                                         // массив для хранения пути к файлу

			strncpy(file_path, str + 5, sizeof(file_path) - 1);                // извлекаем путь к файлу

			file_path[sizeof(file_path) - 1] = '\0';                           // убеждаемся, что строка закончена "null" - символом

			str_get_file_path(file_path);                                      // запрашиваем путь к файлу у пользователя

			char *file_content = str_read_file(file_path);                     // читаем содержимое файла
			if(file_content == NULL) {
				printf("Error!!! Reading File Or Empty Path: %s!!!\n\n", file_path);

				continue;                                                      // пропускаем итерацию, если не удалось прочитать файл
			}

			free(str);                                                         // освобождаем временную строку

			str = file_content;                                                // сохраняем содержимое файла в "str"
		}*/

		///

		/*if(incomplete_expression != NULL && incomplete_expression->is_complete == false) {
			/// Объединяем новый ввод с предыдущим:
			size_t new_len = strlen(combined_input) + strlen(str) + 1;

			combined_input = (char *)realloc(combined_input, new_len);         // перераспределяем память для объединенной строки
			if(combined_input == NULL) {
				printf("Memory Allocation Error!!!\n\n");

				free(str);
				break;                                                         // выходим из цикла при ошибке выделения памяти
			}

			strcat(combined_input, str);                                       // объединяем строки
		} else {
			free(combined_input);                                              // освобождаем предыдущую объединенную строку

			combined_input = strdup(str);                                      // дублируем текущую строку
		}*/

		Expression *result_expression = reader(incomplete_expression); // анализируем объединенную строку

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

	if(combined_input != NULL) {
		free(combined_input);                                                  // освобождаем объединенную строку
	}

	printf("\n");

	return 0;                                                                  // завершаем выполнение
}
