#include "split_tokens.h"

/// Данная функция проверяет соответствие открывающей и закрывающей скобок, используя строки открывающих и закрывающих скобок:
bool str_is_matching_pair(char open, char close)          // используем константу BRACKETS для проверки соответствия
{
	char *open_pos = strchr(OPENING_BRACKETS, open);
	/// Найти индексы открывающей и закрывающей скобок в их строках:
	char *close_pos = strchr(CLOSING_BRACKETS, close);

	/// Если обе скобки найдены, проверим, соответствуют ли их индексы друг другу:
	if(open_pos && close_pos) {
		return (open_pos - OPENING_BRACKETS) == (close_pos - CLOSING_BRACKETS);
	}

	return false;                                         // вернуть "false", если соответствие не найдено
}

/*
    Принцып работы и смысл данной функции:
        Проверяем соответствие открывающей и закрывающей скобок;
        Используя строки открывающих и закрывающих скобок;

    Функция для разделения строки на подстроки:
*/
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
		size_t start = i;                                 // переменная "start" инициализируется значением текущего индекса 'i' --- Это обозначает начало нового токена
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

/*
    Принцып работы и смысл данной функции:
        Выводим токены в требуемом формате;
        Проходя по каждому токену и добавляя разделители;

    Функция для вывода токенов в требуемом формате:
*/
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

/*
    Принцып работы и смысл данной функции:
        Освобождаем память, выделенную под токены и сам массив токенов;
        Предотвращая утечки памяти;

    Освобождаем память, выделенной под токены и сам массив токенов:
*/
void str_free_tokens(char **tokens, size_t num_tokens)    // "tokens" - это массив токенов и "num_tokens" - это количество токенов
{
	for(size_t i = 0; i < num_tokens; ++i) {              // проходит по каждому токену в массиве
		free(tokens[i]);                                  // освобождает память, выделенную под каждый токен
	}

	free(tokens);                                         // освобождает память, выделенную под сам массив токенов
}

/*
    Принцып работы и смысл данной функции:
        Проверяем, является ли символ разделителем;
        Используя объединенную строку разделителей;

    Функция для проверки, является ли символ разделителем(Пробел, запятая или скобка):
*/
char str_is_delimiter(char symbol)
{
	/// Объединяем все константы в одну строку для проверки
	static const char DELIMITERS[] = WHITESPACE PUNCTUATION BRACKETS;
	return strchr(DELIMITERS, symbol) != NULL;            // Проверяем, является ли символ разделителем
}

/*
    Смысл и принцип работы функции:
        1.) Эта функция создает токен указанного типа("token_type") с данными("token_data");
        2.) Если тип токена требует данных('SYM' или 'VAL'), данные копируются с помощью "void strdup()";
*/
Token *str_create_token(char token_type, void *data)      // функция для создания токена указанного типа ("token_type") с данными ("token_data")
{
	Token *token = (Token *)malloc(sizeof(Token));
	if(token) {
		token->token_type = token_type;
		if(strchr(TOKEN_TYPE_WITH_DATA, token_type)) {
			token->token_data = strdup((char *)data);
		} else {
			token->token_data = NULL;
		}
	}

	return token;
}

/// Смысл и принцип работы функции - эта функция создает токен типа 'L'(Левая скобка) без данных:
Token *str_create_token_lp()                              // функция для создания токена типа "LP" ("Left Parenthesis")
{
	return str_create_token('L', NULL);
}

/// Смысл и принцип работы функции - эта функция создает токен типа 'R'(Правая скобка) без данных:
Token *str_create_token_rp()                              // функция для создания токена типа "RP" ("Right Parenthesis")
{
	return str_create_token('R', NULL);
}

/// Смысл и принцип работы функции - эта функция создает токен типа 'S'(Символ) с заданными данными:
Token *str_create_token_sym(const char *data)             // функция для создания токена указанного типа ("'S' - SYMBOL") с заданной ("token_data")
{
	return str_create_token('S', (void *)data);
}

/// Смысл и принцип работы функции - эта функция создает токен типа 'V'(Значение) с заданными данными:
Token *str_create_token_val(const char *data)             // функция для создания токена указанного типа ("'V' - VALUE") с заданной ("token_data")
{
	return str_create_token('V', (void *)data);
}

/*
    Функция для освобождения памяти под структуру "Token", выделенную под нее;
    (Внутри функции используются определенные макросы для проверки типа токена):
*/
void str_free_token2(Token *token)
{
	if(token) {
		if(strchr(TOKEN_TYPE_WITH_DATA, token->token_type)) {
			free(token->token_data);
		}

		free(token);
	}
}

/*
    Смысл и принцип работы функции:
        1.) Эта функция преобразует массив строковых токенов в массив токенов структуры "Token";
        2.) Проходит по каждому входному токену и создает соответствующий токен структуры "Token", сохраняя его в массиве "converted_tokens";
        3.) Увеличивает счетчик преобразованных токенов "num_of_converted_tokens";

    Функция для преобразования массива строковых токенов в массив токенов структуры "Token":
*/
Token **str_convert_tokens(const char **input_tokens, size_t num_tokens, size_t *num_of_converted_tokens)
{
	Token **converted_tokens = (Token **)malloc(num_tokens * sizeof(Token *));
	*num_of_converted_tokens = 0;
	if(!converted_tokens) {
		return NULL;
	}

	for(size_t i = 0; i < num_tokens; ++i) {
		if (strcmp(input_tokens[i], "(") == 0) {
			converted_tokens[i] = str_create_token_lp();
		} else if(strcmp(input_tokens[i], ")") == 0) {
			converted_tokens[i] = str_create_token_rp();
		} else if(isdigit(input_tokens[i][0]) || (input_tokens[i][0] == '-' && isdigit(input_tokens[i][1]))) {
			converted_tokens[i] = str_create_token_val(input_tokens[i]);
		} else {
			converted_tokens[i] = str_create_token_sym(input_tokens[i]);
		}
		if(converted_tokens[i]) {
			(*num_of_converted_tokens)++;
		}
	}

	return converted_tokens;
}

/*
    Смысл и принцип работы функции:
        1.) Эта функция выводит токены структуры "Token" в заданном формате;
        2.) Проходит по каждому токену в массиве и выводит его тип и данные(Если есть) в формате "LP"; "RP"; "SYM[]"; "VAL[]";
*/
void str_print_tokens2(Token **tokens, size_t num_tokens) // функция для необходимого вывода
{
	for(size_t i = 0; i < num_tokens; ++i) {
		Token *token = tokens[i];

		if(token->token_type == 'L') {
			printf("LP");
		} else if(token->token_type == 'R') {
			printf("RP");
		} else if(token->token_type == 'S') {
			printf("SYM[%s]", (char *)token->token_data);
		} else if(token->token_type == 'V') {
			printf("VAL[%s]", (char *)token->token_data);
		}

		if(i < num_tokens - 1) {
			printf(", ");
		}
	}

	printf("\n\n");
}

/*
    Смысл и принцип работы функции:
        1.) Эта функция освобождает память, выделенную под массив токенов структуры "Token" и сами токены;
        2.) Проходит по каждому токену в массиве, освобождая память для каждого из них, а затем освобождает память для самого массива;
*/
void str_free_tokens2(Token **tokens, size_t num_tokens)  // функция для освобождения памяти, веделенной под массив токенов структуры "Token" и сами токены
{
	for(size_t i = 0; i < num_tokens; ++i) {
		str_free_token2(tokens[i]);
	}

	free(tokens);
}
