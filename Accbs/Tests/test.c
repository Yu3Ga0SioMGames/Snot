#include "test.h"

int64_t test_accbs()
{
	char file_path[FILE_SIZE];
	str_get_file_path(file_path, sizeof(file_path));
	char *str = str_read_file(file_path);
	if(str == NULL) {
		return ++error;
	}

	str_print_str(str);

	str_accbs(str);


	size_t num_tokens;
	char **tokens = str_split_str(str, &num_tokens);

	str_print_tokens(tokens, num_tokens);

	str_free_str(str);
	str_free_tokens(tokens, num_tokens);
	return 0;
}
