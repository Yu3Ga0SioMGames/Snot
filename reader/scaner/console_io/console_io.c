#include "console_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1024

char *input()
{
	size_t buffer_size = INITIAL_SIZE;
	char *buffer = malloc(buffer_size);
	if(buffer == NULL) {
		return NULL;
	}

	size_t input_length = 0;
	char temp_buffer[512];

	printf("\nEnter Your Text(End Input With An Empty Line):\n\nInput:\n\n```\n");

	while(1) {
		if(fgets(temp_buffer, sizeof(temp_buffer), stdin) == NULL) {
			free(buffer);
			return NULL;
		}

		size_t temp_length = strlen(temp_buffer);

		if(temp_length == 1 && temp_buffer[0] == '\n') {
			break;
		}

		if(input_length + temp_length + 1 > buffer_size) {
			buffer_size = input_length + temp_length + 1;
			char *new_buffer = realloc(buffer, buffer_size);
			if(new_buffer == NULL) {
				free(buffer);
				return NULL;
			}

			buffer = new_buffer;
		}

		strcpy(buffer + input_length, temp_buffer);
		input_length += temp_length;
	}

	buffer[input_length] = '\0';
	return buffer;
}
