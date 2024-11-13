#include "reader/scaner/split_tokens/test/test.h"                     // заголовочный файл - библиотека
#include "reader/scaner/console_io/console_io.h"
#include "reader/parser/test/test.h"
#include "reader/parser/parser.h"

/*
    int main()
    {
        test_split_tokens();

        return 0;
    }

    Функция "int main()" является точкой входа для выполнения программы на языке 'C':
*/
int main()                                                            // начинаем основную функцию программы
{
	while(1) {
		char *str = NULL;

		while(1) {
			printf("\nMake a Choice('1' or '2'):");
			printf("\n  1.) Read Data From File;");
			printf("\n  2.) Enter Data From Console;\n");
			printf("\nEnter Your Choice Here: ");

			int8_t choice = 0;
			scanf("%d", &choice);
			getchar();
			switch(choice) {
			case 1:
				/// Запрпашиваем путь к файлу и чтение файла:
				char file_path[FILE_SIZE];                            // создаем массив для хранения пути к файлу
				str_get_file_path(file_path, sizeof(file_path));      // запрашиваем путь к файлу у пользователя и сохраняем его в "file_path"

				str = str_read_file(file_path);
				if(str == NULL || strlen(file_path) == 0) {
					continue;
				}

				break;
			case 2:
				str = input();
				if(str == NULL || strlen(str) == 0) {
					continue;
				}

				printf("```\n");

				break;
			default:
				printf("\nInvalid Option Selected!!!\n\n");

				continue;
			}

			break;
		}

		if(str == NULL || strlen(str) == 0) {
			continue;
		}


		str_print_str(str);                                           // печатаем содержимое строки "str"

		str_accbs(str);                                               // проверяем правильность скобочной последовательности в строке


		/// Разбиваем строки на токены:
		size_t num_tokens = 0;                                        // переменная для хранения количества токенов

		/*
		    Разбиваем строку "str" на токены и сохраняем их в массив "tokens",
		    также сохраняем количество токенов в "num_tokens":
		*/
		char **tokens = str_split_str(str, &num_tokens);
		if(tokens == NULL) {                                          // если разбиение строки не удалось, то программа возвращает ошибку
			continue;
		}

		str_print_tokens(tokens, num_tokens);                         // печатаем токены, находящиеся в массиве "tokens"


		// Преобразование и печать токенов:
		size_t num_of_converted_tokens = 0;                           // объявляем переменную для хранения количества преобразованных токенов

		/*
		    Объявляем указатель на массив токенов "converted_tokens" и вызываем функцию "str_convert_tokens",
		    которая принимает массив строковых токенов "tokens",
		    их количество "num_tokens", и указатель на переменную "num_of_converted_tokens";

		    Функция "str_convert_tokens" преобразует строковые токены в структуру "Token" и возвращает указатель на массив этих токенов;

		    Результат функции сохраняется в переменную "converted_tokens":
		*/
		Token **converted_tokens = str_convert_tokens((const char **)tokens, num_tokens, &num_of_converted_tokens);

		if(converted_tokens == NULL) {                                // проверяем, удалось ли выделить память и преобразовать токены
			continue;
		}

		str_print_tokens2(converted_tokens, num_of_converted_tokens); // выводим токены в заданном порядке


		/// Разбор токенов и создание выражения:
		Expression *parsed_expression = parse2(converted_tokens, num_of_converted_tokens);
		if(parsed_expression != NULL) {
			int8_t depth = 1;
			print_expression(parsed_expression, depth);
			printf("\n");
		}


		/// Освобождаем память:
		str_free_str(str);                                            // освобождаем память, выделенную под строку
		str_free_tokens(tokens, num_tokens);                          // освобождаем память, выделенную под токены в массиве
		str_free_tokens2(converted_tokens, num_of_converted_tokens);  // освобождаем память, выделенную под преобразованные токены в массиве
		free_expression(parsed_expression);

		printf("\nDo You Want To Perform Another Action?(\"Yes\" = '0' or \"no\" = another number): ");

		int8_t continue_choice = 0;

		scanf("%d", &continue_choice);

		getchar();

		if(continue_choice != 0) {
			break;
		}
	}

	return 0;                                                         // завершаем выполнение
}
