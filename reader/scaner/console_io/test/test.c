#include "test.h"

int test_console_input()                  // тестовая функция для консольного ввода
{
	char *str = input();                  // вызываем функцию ввода строки
	if(str == NULL || strlen(str) == 0) { // проверяем, что строка не пуста и корректна
		return ERROR;                     // возвращаем ошибку, если строка пуста
	}

	str_print_str(str);                   // печатаем введенную строку

	str_free_str(str);                    // освобождаем память, выделенную под строку
	return 0;                             // возвращаем 0, если все прошло успешно
}
