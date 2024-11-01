#include "accbs.h" // подключаем ссылку на библиотеку-файл, где содержатся определения слудующих функций

thread_local int64_t error = 0; // код ошибки

bool str_is_matching_pair(char open, char close)                      // Используем константу BRACKETS для проверки соответствия
{
	char *open_pos = strchr(BRACKETS, open);                          // открытые скобки
	char *close_pos = strchr(BRACKETS, close);                        // закрытые скобки

	return (open_pos && close_pos && (close_pos - open_pos) == 1);
}

/// Функция "str_print" печатает ЛЮБУЮ строку, а в параметры принимает указатель на строку:
void str_print_str(const char *str)
{
	printf("\nOutput:\n\n```\n%s```\n\n", str);                       // печать
}

/*
    Функция "str_free" очищает ЛЮБУЮ строку(Вернее выделеную память под неё),
    в параметры принимает указатель на строку:
*/
void str_free_str(char *str)
{
	free(str);                                                        // освобождение памяти
}

/// В функцию "str_accbs" передаём содержимое файла:
void str_accbs(const char *str)
{
	/// Создаём стёк длиной, равной длине строки, и переменную "top", которая будет указывать на вершину стёка:
	size_t length = strlen(str);                                                      // узнаём длину поолученной строки
	char *stack = (char *)malloc(length);                                             // создаем стёк для хранения открывающих скобок
	int64_t top = -1;                                                                 // инициализируем вершину стёка

	printf("The text read:\n\n```\n");                                                // пользовательский текст, так, Для удобства

	for(size_t i = 0; i < length; ++i) {                                              // перебираем всю строку
		printf("%c", str[i]);                                                         // печатаем всё, что успели прочитать
		if(strchr(BRACKETS, str[i])) {                                                // добавляем все виды открывающих скобок в стёк
			if(strchr(OPENING_BRACKETS, str[i])) {
				stack[++top] = str[i];
			} else {                                                                  // проверяем их закрытие
				if(top == -1) {                                                       // проверяем, не пуст ли стёк
					++error;                                                          // код ошибки
					printf("\n```\n\nError Code = %lld\n\n", error);                  // печатаем какой-то текст
					str_free_str(stack);                                              // освобождаем память

					return;                                                           // возращаем функцию
				}

				char open_brace = stack[top--];                                       // извлекаем верхний элемент из стёка
				if(!str_is_matching_pair(open_brace, str[i])) {                       // проверяем соответствие открывающей и закрывающей скобок
					++error;                                                          // код ошибки
					printf("\n```\n\nError Code = %lld\n\n", error);                  // печатаем какой-то текст
					str_free_str(stack);                                              // освобождаем память

					return;                                                           // возращаем функцию
				}

			}
		}
	}

	/// Проверяем, пуст ли стёк после обработки всей строки:
	if(top != -1) {                                                                   // проверяем, пуст ли стёк после обработки всей строки
		++error;                                                                      // код ошибки
		printf("\n```\n\nError Code = %lld\n\n", error);                              // печатаем какой-то текст
	} else {                                                                          // в противном случаи
		printf("```\n\nAll parentheses are balanced!\n\n");                           // печатаем какой-то текст
	}

	str_free_str(stack);                                                              // освобождаем память
}

/*
    Функция str_get_file_path принимает два аргумента:
        1.) Указатель "file_path" для хранения пути к файлу;
        2.) Размер буфера файла по пути;
*/
void str_get_file_path(char *file_path, size_t file_size)
{
	printf("\nEnter File Path: ");  // печать

	/*
	    Используем функцию "fgets" для чтения строки из стандартного ввода("stdin") и сохранения ее в file_path;
	    Чтение происходит до тех пор, пока не достигнута максимальная длина (file_size) или не встретится символ новой строки:
	*/
	if(fgets(file_path, file_size, stdin) != NULL) {
		/*
		    Если возвращено не NULL,
		    то вычисляем размер-длину(В нашем случаи) введенной строки в файле с помощью функции "strlen"
		    и сохраняет ее в переменную length:
		*/
		size_t length = strlen(file_path);

		/*
		    Далее, проверяем файл на наличие чего-либо(С помощью размера-длины)
		    и на тот случай, если последний символ в файле-строке - это перевод на следующую строку:
		*/
		if(length > 0 && file_path[length - 1] == '\n') {
			/// После, последний символ строки заменяем с символа перевода на след строчку, на символ конца строки:
			file_path[length - 1] = '\0';
		}
	}
}

/// В функцию "str_read_file" передаём путь к файлу:
char *str_read_file(const char *file_path)
{
	/*
	    Далее используем функцию "fopen" для открытия файла на чтение в текстовом режиме
	    ("rt" - Это режим позволяющий читать файлы в любом ТЕКСТОВОМ формате);
	    Указатель "file" будет указывать на результат функции "fopen", ну то есть на открытый файл):
	*/
	FILE *file = fopen(file_path, "rt");
	if(file == NULL) {              // проверяем, не пуст ли указатель:
		++error;                    // код ошибки

		return NULL;                // в случаи ошибки - заканчиваем функцию возращением "ничего"
	}

	/// Используем функцию "fseek" для перемещения указателя на файл в конец файла(Это нужно для определения размера файла):
	fseek(file, 0, SEEK_END);
	/// Далее, используем функцию "ftell", которая возвращает текущую позицию указателя в файле(В данном случае - это размер файла):
	long long file_size = ftell(file);
	/// Снова используется функция "fseek" для перемещения указателя на файл, обратно в начало файла:
	fseek(file, 0, SEEK_SET);

	/// Выделяем память для хранения содержимого файла, плюс один дополнительный байт для символа конца строки("\0"):
	char *str = (char *)malloc(file_size + 1);
	if(str == NULL) {               // проверяем, не пуст ли указатель:
		++error;                    // код ошибки
		fclose(file);               // закрываем файл

		return NULL;                // в случаи ошибки - заканчиваем функцию возращением "ничего"
	}

	fread(str, 1, file_size, file); // используем функцию "fread" для чтения содержимого файла и сохранения его в выделенную память "str"
	str[file_size] = '\0';          // в конец строки добавляем символ конца строки("\0"), чтобы корректно завершить строку

	fclose(file);                   // закрываем файл
	return str;                     // заканчиваем функцию возращаем содержимое файла
}

/// Функция для проверки, является ли символ разделителем(Пробел, запятая или скобка):
char str_is_delimiter(char symbol)
{
	/// Объединяем все константы в одну строку для проверки
	static const char DELIMITERS[] = WHITESPACE PUNCTUATION BRACKETS;
	return strchr(DELIMITERS, symbol) != NULL;            // Проверяем, является ли символ разделителем
}

/// Функция для разделения строки на подстроки:
char **str_split_str(const char *str, size_t *num_tokens) // "str" - это входная строка, "num_tokens" - это указатель на количество токенов
{
	size_t length = strlen(str);                          // длина строки "str"
	char **tokens = NULL;                                 // массив(Двойной указатель) для хранения токенов
	*num_tokens = 0;                                      // количество токенов, инициализируется 0
	for(size_t i = 0; i < length;) {                      // обход строки
		/// Пропускаем разделители:
		/*
		    Цикл "while" работает, пока 'i' меньше длины строки "length",
		    и текущий символ "str[i]" является разделителем(Пробелом, скобкой(Любого типа), запятой)
		    Если это условие выполняется, продолжаем выполнение тела цикла:
		*/
		while(i < length && str_is_delimiter(str[i])) {   // пропускаем все разделители(Пробелы, запятые и скобки)
			if(!isspace(str[i])) {                        // если символ не является пробелом, то есть, если это скобка или запятая, то...
				/// Добавляем его как отдельный токен:

				/*
				    Увеличиваем размер массива "tokens" на один элемент.
				    Функция "realloc" изменяет размер ранее выделенного блока памяти, чтобы поместить дополнительный указатель на новую строку:
				*/

				/// Перевыделение памяти для массива "tokens":
				tokens = realloc(tokens, (*num_tokens + 1) * sizeof(char *));

				/*
				    Так как это будет одиночный символ(Скобка или запятая), то достаточно выделить память для двух символов:
				    самого символа и символа конца строки "\0":
				*/

				/// Выделение памяти для нового токена:
				tokens[*num_tokens] = malloc(2 * sizeof(char));

				tokens[*num_tokens][0] = str[i];          // копируем текущий символ из строки "str" в новый токен
				tokens[*num_tokens][1] = '\0';            // завершаем токен символом конца строки "\0"
				++(*num_tokens);                          // увеличиваем количество токенов на один
			}

			++i;                                          // переходим к следующему символу в строке
		}

		/// Начало нового токена:
		size_t start = i; // переменная "start" инициализируется значением текущего индекса 'i' --- Это обозначает начало нового токена
		/// Цикл продолжается, пока 'i' меньше длины строки("Length") и текущий символ "str[i]" не является разделителем:
		while(i < length && !str_is_delimiter(str[i])) {
			++i;

			/*
			    Индекс 'i' увеличивается, чтобы пройти по каждому символу, не являющемуся разделителем,
			    пока не встретится следующий разделитель или конец строки:
			*/
		}

		/// Добавляем токены в массив:
		if(i > start) {                                   // если токен не пустой, то выделяем память и копируем токен, то есть, добавляем его в массив
			size_t token_length = i - start;              // инициализируем значением длины токена, которое равно разнице между текущим значением 'i' и "start"

			/*
			    Изменяем размер ранее выделенного блока памяти для хранения указателей на строки,
			    чтобы поместить дополнительный указатель на новый токен:
			*/
			tokens = realloc(tokens, (*num_tokens + 1) * sizeof(char *));

			/*
			    Выделяем память для нового токена,
			    размер выделяемой памяти равен длине токена плюс один дополнительный байт для символа конца строки "\0":
			*/
			tokens[*num_tokens] = malloc((token_length + 1) * sizeof(char));

			/// Копируем токен из исходной строки "str", начиная с "start" и длиной "token_length":
			strncpy(tokens[*num_tokens], &str[start], token_length);
			tokens[*num_tokens][token_length] = '\0';     // добавляем символ конца строки "\0" в конец токена, чтобы правильно завершить строку
			++(*num_tokens);                              // увеличивается количество токенов на один
		}
	}

	return tokens;                                        // возращаем хранителя токенов - Массив
}

/// Функция для вывода токенов в требуемом формате:
void str_print_tokens(char **tokens, size_t num_tokens)   // "tokens" - это массив токенов и "num_tokens" - это количество токенов
{
	printf("'");                                          // начало списка токенов
	for(size_t i = 0; i < num_tokens; ++i) {              // проходит по каждому токену в массиве
		printf("%s", tokens[i]);                          // печатает текущий токен
		if(i < num_tokens - 1) {                          // если текущий токен не последний, то...
			printf("', '");                               // добавляет разделитель ", " между токенами
		}
	}

	printf("'\n\n");                                      // завершаем вывод, добавляя завершающую одинарную кавычку и новую строку
}

/// Освобождаем память, выделенной под токены и сам массив токенов:
void str_free_tokens(char **tokens, size_t num_tokens)    // "tokens" - это массив токенов и "num_tokens" - это количество токенов
{
	for(size_t i = 0; i < num_tokens; ++i) {              // проходит по каждому токену в массиве
		free(tokens[i]);                                  // освобождает память, выделенную под каждый токен
	}

	free(tokens);                                         // освобождает память, выделенную под сам массив токенов
}
