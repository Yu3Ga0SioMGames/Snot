#include "console_io.h"                                              // подключаем заголовочный файл для работы с консольным вводом-выводом

#include <stdio.h>                                                   // подключаем стандартную библиотеку ввода-вывода
#include <stdlib.h>                                                  // подключаем библиотеку для работы с памятью
#include <string.h>                                                  // подключаем библиотеку для работы со строками

#define INITIAL_SIZE 1024                                            // определяем начальный размер буфера

char *input()
{
	size_t buffer_size = INITIAL_SIZE;                               // начальный размер буфера
	char *buffer = malloc(buffer_size);                              // выделяем память для буфера
	if(buffer == NULL) {                                             // проверяем, успешно ли выделена память
		return NULL;                                                 // если не успешно, возвращаем "NULL"
	}

	size_t input_length = 0;                                         // длина текущего ввода
	char temp_buffer[512];                                           // временный буфер для хранения введенной строки

	while(1) {
		if(fgets(temp_buffer, sizeof(temp_buffer), stdin) == NULL) { // читаем строку из ввода
			free(buffer);                                            // освобождаем память в случае ошибки
			return NULL;                                             // возвращаем "NULL"
		}

		size_t temp_length = strlen(temp_buffer);                    // определяем длину временной строки

		if(temp_length == 1 && temp_buffer[0] == '\n') {             // проверяем, является ли введенная строка пустой(Только символ новой строки)
			break;                                                   // выходим из цикла, если введена пустая строка
		}

		if(input_length + temp_length + 1 > buffer_size) {           // проверяем, нужно ли увеличить размер буфера
			buffer_size = input_length + temp_length + 1;            // увеличиваем размер буфера до нового размера
			char *new_buffer = realloc(buffer, buffer_size);         // перевыделяем память для буфера
			if(new_buffer == NULL) {                                 // проверяем, успешно ли перевыделена память
				free(buffer);                                        // освобождаем старый буфер в случае ошибки
				return NULL;                                         // возвращаем "NULL"
			}

			buffer = new_buffer;                                     // обновляем указатель на буфер
		}

		strcpy(buffer + input_length, temp_buffer);                  // копируем временную строку в основной буфер
		input_length += temp_length;                                 // увеличиваем длину текущего ввода
	}

	buffer[input_length] = '\0';                                     // завершаем строку нулевым символом
	return buffer;                                                   // возвращаем указатель на буфер
}
