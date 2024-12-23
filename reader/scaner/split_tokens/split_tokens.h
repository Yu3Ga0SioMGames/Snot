/*
    Этот директив препроцессора проверяет, не определен ли макрос "SPLIT_TOKENS_H_INCLUDED".
    Если макрос не определен, код внутри условного блока будет обработан:
*/
#ifndef SPLIT_TOKENS_H_INCLUDED

/*
    Определяет макрос "SPLIT_TOKENS_H_INCLUDED".
    Это предотвращает многократное включение этого заголовочного файла в один и тот же файл.
    Благодаря этому директиву, следующий раз при включении "SPLIT_TOKENS_H_INCLUDED"
    компилятор пропустит содержимое между "#ifndef" и "#endif":
*/
#define SPLIT_TOKENS_H_INCLUDED

/*
    Подключаем заголовочный файл, в котором содержатся общие определения и функции,
    используемые в других файлах:
*/
#include "../../../main_common.h"

/*
    Подключаем заголовочный файл, в котором содержатся функции и определения,
    связанные со скобочными алгоритмами:
*/
#include "../accbs/accbs.h"

/// Подключаем заголовочный файл, в котором содержатся тестовые функции:
#include "../accbs/test/test.h"


#define TOKEN_TYPE_WITH_DATA "SV"                            // символы содержащие данные
#define TOKEN_TYPE_WITHOUT_DATA "LR"                         // символы несодержащие данные


typedef
struct _token
{
	char token_type;                                         // первое поле(Для символов)
	void *token_data;                                        // второе поле(Для дополнительно параметра)
} Token;                                                     // определяем структуру "Token"


/// Данная функция проверяет соответствие открывающей и закрывающей скобок, используя строки открывающих и закрывающих скобок:
bool str_is_matching_pair(char, char);


/*
    Принцып работы и смысл данной функции:
        Проверяем, является ли символ разделителем;
        Используя объединенную строку разделителей;

    Функция для проверки, является ли символ разделителем(Пробел, запятая или скобка):
*/
char str_is_delimiter(char);                                 // функция для проверки, является ли символ разделителем(Пробел, запятая или скобка)

/*
    Принцып работы и смысл данной функции:
        Проверяем соответствие открывающей и закрывающей скобок;
        Используя строки открывающих и закрывающих скобок;

    Функция для разделения строки на подстроки:
*/
char **str_split_str(const char *, size_t *);                // функция для разделения строки на подстроки


/*
    Смысл и принцип работы функции:
        1.) Эта функция освобождает память, выделенную под один токен;
        2.) Если токен содержит данные, память под эти данные также освобождается;
*/
void str_free_token(Token *);                                // функция для освобождения памяти, веделенный под токен

/*
    Функция для освобождения памяти под структуру "Token", выделенную под нее;
    (Внутри функции используются определенные макросы для проверки типа токена):
*/
void str_free_token2(Token *token);

/*
    Принцып работы и смысл данной функции:
        Освобождаем память, выделенную под токены и сам массив токенов;
        Предотвращая утечки памяти;

    Освобождаем память, выделенной под токены и сам массив токенов:
*/
void str_free_tokens(char **, size_t);                       // освобождаем память, выделенной под токены и сам массив токенов

/*
    Принцып работы и смысл данной функции:
        Выводим токены в требуемом формате;
        Проходя по каждому токену и добавляя разделители;

    Функция для вывода токенов в требуемом формате:
*/
void str_print_tokens(char **, size_t);                      // функция для вывода токенов в требуемом формате

/*
    Смысл и принцип работы функции:
        1.) Эта функция освобождает память, выделенную под массив токенов структуры "Token" и сами токены;
        2.) Проходит по каждому токену в массиве, освобождая память для каждого из них, а затем освобождает память для самого массива;
*/
void str_free_tokens2(Token **, size_t);                     // функция для освобождения памяти, веделенной под массив токенов структуры "Token" и сами токены

/*
    Смысл и принцип работы функции:
        1.) Эта функция выводит токены структуры "Token" в заданном формате;
        2.) Проходит по каждому токену в массиве и выводит его тип и данные(Если есть) в формате "LP"; "RP"; "SYM[]"; "VAL[]";
*/
void str_print_tokens2(Token **, size_t);                    // функция для необходимого вывода


/// Смысл и принцип работы функции - эта функция создает токен типа 'L'(Левая скобка) без данных:
Token *str_create_token_lp();                                // функция для создания токена типа "LP" ("Left Parenthesis")

/// Смысл и принцип работы функции - эта функция создает токен типа 'R'(Правая скобка) без данных:
Token *str_create_token_rp();                                // функция для создания токена типа "RP" ("Right Parenthesis")

/*
    Смысл и принцип работы функции:
        1.) Эта функция создает токен указанного типа("token_type") с данными("token_data");
        2.) Если тип токена требует данных('SYM' или 'VAL'), данные копируются с помощью "void strdup()";
*/
Token *str_create_token(char, void *);                       // функция для создания токена указанного типа ("token_type") с данными ("token_data")

/// Смысл и принцип работы функции - эта функция создает токен типа 'S'(Символ) с заданными данными:
Token *str_create_token_sym(const char *);                   // функция для создания токена указанного типа ("'S' - SYMBOL") с заданной ("token_data")

/// Смысл и принцип работы функции - эта функция создает токен типа 'V'(Значение) с заданными данными:
Token *str_create_token_val(const char *);                   // функция для создания токена указанного типа ("'V' - VALUE") с заданной ("token_data")

/*
    Смысл и принцип работы функции:
        1.) Эта функция преобразует массив строковых токенов в массив токенов структуры "Token";
        2.) Проходит по каждому входному токену и создает соответствующий токен структуры "Token", сохраняя его в массиве "converted_tokens";
        3.) Увеличивает счетчик преобразованных токенов "num_of_converted_tokens";
*/
Token **str_convert_tokens(const char **, size_t, size_t *); // функция для преобразования массива строковых токенов в массив токенов структуры "Token"


/*
    Закрывает условный блок препроцессора, начатый директивой "#ifndef".
    Если макрос "SPLIT_TOKENS_H_INCLUDED" не был определен до этого,
    код между "#ifndef" и "#endif" будет включен:
*/
#endif

/// Смысл этого заголовочного файла в использовании алгоритмических функций.
