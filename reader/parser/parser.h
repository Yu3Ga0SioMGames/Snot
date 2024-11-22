#ifndef PARSER_H_INCLUDED

/// Защита от двойного включения заголовочного файла:

#define PARSER_H_INCLUDED


#include <limits.h>
#include <stdbool.h>


#include "../../tests/stack/stack.h"                               // подключаем заголовочный файл для работы с стеком
#include "../../data_structures/list/list.h"                       // подключаем заголовочный файл для работы со списками
#include "../scaner/split_tokens/split_tokens.h"                   // подключаем заголовочный файл для работы с разбивкой на токены


#define ELEMENT_SYMBOL 0                                           // символический элемент
#define ELEMENT_VALUE 1                                            // элемент значения
#define ELEMENT_EXPRESSION 2                                       // элемент выражения


typedef
struct _symbol                                                     // структура для символов
{
	char *symbol_name;                                             // имя символа
} Symbol;

typedef
struct _value                                                      // структура для значений
{
	uint64_t value_type;                                           // тип значения
	void *value_data;                                              // данные значения
} Value;

typedef
struct _expression                                                 // структура для выражений
{
	List *element_list;                                            // список элементов выражения
	bool is_complete;                                              // переменная для проверки завершенности выражения
} Expression;

typedef
struct _expression_element                                         // структура для элементов выражения
{
	uint64_t expression_element_type;                              // тип элемента выражения
	union {
		Symbol symbol;                                             // символ
		Value value;                                               // значение
		Expression expression;                                     // вложенное выражение
	};
} ExpressionElement;


Symbol *create_symbol(char *);                                     // создание нового символа

Expression *create_expression();                                   // создание нового выражения
Expression *parse(Token **, size_t, Expression *);                 // функция разбора токенов в выражение

Value *create_value(uint64_t, void *);                             // создание нового значения

char *tokens_to_string(Token **, size_t);                          // функция для преобразования массива токенов в строку

bool is_matching_pair(char, char);                                 // проверяем соответствия пары символов(Скобок)
bool is_expression_complete(const char *);                         // проверяем завершено ли выражение

void free_value(Value *);                                          // освобождение памяти, выделенной под значение
void free_symbol(Symbol *);                                        // освобождение памяти, выделенной под символ
void free_expression(Expression *);                                // освобождение памяти, выделенной под выражение
void print_expression(Expression *, long long, char *);                    // печать выражения
void free_expression_element(ExpressionElement *);                 // освобождение памяти, выделенной под элемент выражения
void restore_expression_stack(Stack *, Expression *);              // функция для восстановления стека выражений

int append_to_expression(Expression *, ExpressionElement *);       // добавление элемента к выражению

ExpressionElement *create_expression_element(uint64_t, void *);    // создание нового элемента выражения
ExpressionElement *create_expression_element_from_token(Token *);  // функция для создания элемента выражения из токена


#endif                                                             // завершение защиты от двойного включения
