#include "console_io.h"                                              // подключаем заголовочный файл для работы с консольным вводом-выводом

#include <stdio.h>                                                   // подключаем стандартную библиотеку ввода-вывода
#include <stdlib.h>                                                  // подключаем библиотеку для работы с памятью
#include <string.h>                                                  // подключаем библиотеку для работы со строками

#include "../../../data_structures/container/container.h"

char *input(FILE *input_file)
{
	size_t buffer_size = 1024;
	size_t free_size = buffer_size;

	char *input_buffer = (char *)malloc(buffer_size);
	if(input_buffer == NULL) { // проверяем, успешно ли выделена память
		// TODO: SIGNAL_ERROR
		return NULL;           // если не успешно, возвращаем "NULL"
	}

	size_t elements_count = 0;
	size_t read_count = 0;

	const size_t element_size = sizeof(char);

	while((read_count = fread(input_buffer + elements_count * element_size,
	                          element_size,
	                          free_size / element_size,
	                          input_file)) != 0) {
		free_size -= read_count;
		elements_count += read_count;

		if(free_size < element_size) {
			input_buffer = (char *)realloc(input_buffer, buffer_size * 2);
			free_size += buffer_size;
			buffer_size *= 2;
		}
	}

	*(input_buffer + elements_count * element_size) = 0;

	return input_buffer;
}
