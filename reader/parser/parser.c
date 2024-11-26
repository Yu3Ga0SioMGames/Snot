#include "parser.h"                                                                      // подключение заголовочного файла

Symbol *create_symbol(char *input_name)
{
	Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));                                   // выделение памяти для структуры "Symbol"
	if(symbol == NULL) {
		return NULL;                                                                     // проверка успешности выделения памяти
	}

	if(input_name == NULL) {
		symbol->symbol_name = NULL;                                                      // обработка случая, когда имя символа не задано
	}

	symbol->symbol_name = strdup(input_name);                                            // копирование имени символа

	return symbol;                                                                       // возвращение указателя на созданный символ
}

ValueToken *create_value_token(uint64_t value_type, void *value_data)
{
	ValueToken *value = (ValueToken *)malloc(sizeof(ValueToken));                        // выделение памяти для структуры "Value"
	if(value == NULL) {
		return NULL;                                                                     // проверка успешности выделения памяти
	}

	value->value_type = value_type;                                                      // установка типа значения
	value->value_data = value_data;                                                      // установка данных значения

	return value;                                                                        // возвращение указателя на созданное значение
}

Expression *create_expression()
{
	Expression *expression = (Expression *)malloc(sizeof(Expression));                   // выделение памяти для структуры "Expression"
	if(expression == NULL) {
		return NULL;                                                                     // проверка успешности выделения памяти
	}

	expression->element_list = create_list();                                            // создание списка элементов выражения
	if(expression->element_list == NULL) {
		free(expression);                                                                // освобождение памяти в случае ошибки
		return NULL;
	}

	return expression;                                                                   // возвращение указателя на созданное выражение
}

ExpressionElement *create_expression_element(uint64_t input_expression_element_type, void *input_data)
{
	ExpressionElement *element = (ExpressionElement *)malloc(sizeof(ExpressionElement)); // выделение памяти для элемента выражения
	if(element == NULL) {
		return NULL;                                                                     // проверка успешности выделения памяти
	}

	element->expression_element_type = input_expression_element_type;                    // установка типа элемента

	switch(input_expression_element_type) {
	case ELEMENT_SYMBOL:
		element->symbol = *((Symbol *)input_data);                                       // установка символа

		break;
	case ELEMENT_VALUE:
		element->value = *((ValueToken *)input_data);                                    // установка значения

		break;
	case ELEMENT_EXPRESSION:
		element->expression = *((Expression *)input_data);                               // установка подвыражения

		break;
	}

	return element;                                                                      // возвращение указателя на созданный элемент
}

void free_symbol(Symbol *symbol)
{
	if(symbol == NULL) {
		return;                                                                          // проверка на "NULL"
	}

	if(symbol->symbol_name != NULL) {
		free(symbol->symbol_name);                                                       // освобождение памяти, выделенной под имя символа
		symbol->symbol_name = NULL;
	}

	free(symbol);                                                                        // освобождение памяти, выделенной под символ
}

void free_value_token(ValueToken *value)
{
	if(value == NULL) {
		return;                                                                          // проверка на "NULL"
	}

	if(value->value_data != NULL) {
		// free(value->value_data);                                                      // освобождение памяти, выделенной под данные значения
	}

	free(value);                                                                         // освобождение памяти, выделенной под значение
}

void free_expression(Expression *expression)
{
	if(expression == NULL) {
		return;                                                                          // проверка на "NULL"
	}

	free_list(expression->element_list);                                                 // освобождение памяти, выделенной под список элементов
	free(expression);                                                                    // освобождение памяти, выделенной под выражение
}

void free_expression_element(ExpressionElement *element)
{
	if(element == NULL) {
		return;                                                                          // проверка на "NULL"
	}

	switch(element->expression_element_type) {
	case ELEMENT_SYMBOL:
		free_symbol(&(element->symbol));                                                 // освобождение символа
		break;
	case ELEMENT_VALUE:
		free_value_token(&(element->value));                                                   // освобождение значения
		break;
	case ELEMENT_EXPRESSION:
		free_expression(&(element->expression));                                         // освобождение подвыражения
		break;
	}

	free(element);                                                                       // освобождение памяти, выделенной под элемент
}

int append_to_expression(Expression *expression, ExpressionElement *element)
{
	return append_to_list(expression->element_list, element);                            // добавление элемента в список выражения
}

void print_expression(Expression *expression, long long depth, char *text)
{
	if(expression == NULL) {                                                             // проверка на "NULL"
		return;
	}

	if(text != NULL) {
		printf("%s", text);
	}

	Node *current = expression->element_list->first;

	while(current != NULL) {                                                             // перебираем элементы списка
		ExpressionElement *element = (ExpressionElement *)current->data;

		for(int i = 0; i < depth; ++i) {
			printf("  ");                                                                // отступ для вложенности
		}

		switch(element->expression_element_type) {                                       // выводим данные в зависимости от типа элемента
		case ELEMENT_SYMBOL:
			printf("Symbol: %s\n", element->symbol.symbol_name);
			break;
		case ELEMENT_VALUE:
			printf("Value:  %d\n", (int)(element->value.value_data));                    // используем тип "int" для вывода

			break;
		case ELEMENT_EXPRESSION:
			printf("Expression:\n");

			print_expression(&element->expression, depth + 1, NULL);                     // рекурсивный вызов для подвыражений с увеличением "depth"

			break;
		}

		current = current->next;
	}
}

char *tokens_to_string(Token **tokens, size_t num_tokens)                                // функция для преобразования массива токенов в строку
{
	if(tokens == NULL || num_tokens == 0) {
		return NULL;
	}

	size_t total_length = 0;                                                             // вычисляем необходимый размер строки
	for(size_t i = 0; i < num_tokens; ++i) {
		if(tokens[i]->token_data != NULL) {
			total_length += strlen((char *)tokens[i]->token_data);
		}

		total_length += 1;                                                               // для учета символа токена
	}

	char *result = (char *)malloc((total_length + 1) * sizeof(char));                    // выделяем память для строки
	if(result == NULL) {
		return NULL;
	}

	result[0] = '\0';                                                                    // начальная инициализация строки

	for(size_t i = 0; i < num_tokens; ++i) {                                             // заполняем строку данными токенов
		if(tokens[i]->token_data != NULL) {
			strcat(result, (char *)tokens[i]->token_data);
		}

		strncat(result, &tokens[i]->token_type, 1);
	}

	return result;
}

bool is_expression_complete(const char *expression)
{
	char *stack = (char *)malloc(strlen(expression) + 1);                                // используем стек для проверки корректного открывания и закрывания скобок
	if(stack == NULL) {
		return false;                                                                    // ошибка выделения памяти
	}

	long long top = -1;                                                                  // индекс верхнего элемента стека

	for(size_t i = 0; i < strlen(expression); ++i) {
		if(expression[i] == '(') {
			stack[++top] = expression[i];                                                // добавляем открывающую скобку в стек
		} else if(expression[i] == ')') {
			if(top == -1 || !is_matching_pair(stack[top], expression[i])) {
				free(stack);

				return false;                                                            // неправильная скобочная последовательность
			}

			--top;                                                                       // удаляем элемент из стека
		}
	}

	bool is_complete = (top == -1);                                                      // выражение завершено, если стек пустой

	free(stack);
	return is_complete;
}

bool is_matching_pair(char open, char close)
{
	return (open == '(' && close == ')');                                                // проверка соответствия открывающей и закрывающей скобок
}

void restore_expression_stack(Stack *stack, Expression *incomplete_expression)
{
	if(stack == NULL || incomplete_expression == NULL) {
		return;                                                                          // возвращаемся, если стек или выражение пустые
	}

	stack_push(stack, incomplete_expression);                                            // помещаем незавершенное выражение в стек

	while(list_length(((Expression *)(stack_peek(stack)))->element_list)) {
		Expression *top = (Expression *)stack_peek(stack);

		ExpressionElement *last = (ExpressionElement *)(top->element_list->last->data);

		if(last->expression_element_type == ELEMENT_EXPRESSION && last->expression.is_complete == false) {
			delete_last_from_list(top->element_list);

			stack_push(stack, &(last->expression));
		} else {
			break;
		}
	}
}

Expression *collect_expression_stack(Stack *stack)
{
	if(stack == NULL) {
		return NULL;                                                                     // возвращаемся, если стек или выражение пустые
	}

	bool complete = stack->stack_size == 1;

	while(stack->stack_size > 1) {
		Expression *last = (Expression *)stack_pop(stack);
		ExpressionElement *last_element = create_expression_element(ELEMENT_EXPRESSION, last);
		append_to_expression(((Expression *)(stack_peek(stack))), last_element);
	}

	Expression *result = ((Expression *)(stack_pop(stack)));

	result->is_complete = complete;

	return result;
}

Expression *parse(Token **converted_tokens, size_t token_count, Expression *incomplete_expression)
{
	Stack *expression_stack = create_stack();                                            // создаем стек выражений
	if(expression_stack == NULL) {
		printf("Error!!! Failed To Create Stack!!!\n\n");

		return incomplete_expression;
	}

	if(incomplete_expression != NULL) {
		restore_expression_stack(expression_stack, incomplete_expression);               // восстанавливаем стек, если есть незавершенное выражение
	}

	/// Создаем корневое выражение:
	Expression *root_expression = incomplete_expression ?
	                              incomplete_expression : create_expression();

	if(root_expression == NULL) {
		printf("Error!!! Failed To Create Root Expression!!!\n\n");

		free_stack(expression_stack);
		return incomplete_expression;
	}

	if(incomplete_expression == NULL) {
		stack_push(expression_stack, root_expression);                                   // помещаем корневое выражение в стек
	}

	for(size_t i = 0; i < token_count; ++i) {                                            // проходим по всем токенам
		Token *token = converted_tokens[i];

		if(token->token_type == 'L') {                                                   // обрабатываем левую скобку
			Expression *new_expression = create_expression();
			if(new_expression == NULL) {
				printf("Error!!! Failed To Create New Expression!!!\n\n");

				root_expression->is_complete = false;

				return incomplete_expression;
			}

			new_expression->is_complete = false;

			stack_push(expression_stack, new_expression);                                // помещаем новое выражение в стек
		} else if(token->token_type == 'R') {                                            // обрабатываем правую скобку
			if(expression_stack->stack_size < 2) {
				printf("Error!!! Mismatched Parentheses Or Stack Underflow!!!\n\n");

				root_expression->is_complete = false;

				return incomplete_expression;
			}

			Expression *current_expression = stack_pop(expression_stack);                // извлекаем текущее выражение из стека
			current_expression->is_complete = true;

			Expression *parent_expression = stack_peek(expression_stack);                // получаем родительское выражение

			ExpressionElement *element = create_expression_element(ELEMENT_EXPRESSION, current_expression);
			if(element == NULL) {
				printf("Error!!! Failed To Create Expression Element!!!\n\n");

				root_expression->is_complete = false;

				free_expression(current_expression);
				return incomplete_expression;
			}

			if(append_to_expression(parent_expression, element) != 0) {
				printf("Error!!! Failed To Append Expression Element!!!\n\n");

				root_expression->is_complete = false;

				free_expression_element(element);
				free_expression(current_expression);
				return incomplete_expression;
			}
		} else if(token->token_type == 'S') {                                            // обрабатываем символ
			Symbol *symbol = create_symbol((char *)token->token_data);
			if(symbol == NULL) {
				printf("Error!!! Failed To Create Symbol!!!\n\n");

				root_expression->is_complete = false;

				return incomplete_expression;
			}

			ExpressionElement *element = create_expression_element(ELEMENT_SYMBOL, symbol);
			if(element == NULL) {
				printf("Error!!! Failed To Create Symbol Element!!!\n\n");

				root_expression->is_complete = false;

				free_symbol(symbol);
				return incomplete_expression;
			}

			Expression *current_expression = stack_peek(expression_stack);
			if(append_to_expression(current_expression, element) != 0) {
				printf("Error!!! Failed To Append Symbol Element!!!\n\n");

				root_expression->is_complete = false;

				free_expression_element(element);
				return incomplete_expression;
			}
		} else if (token->token_type == 'V') {                                           // обрабатываем значение
			char *endptr;

			errno = 0;
			int value = strtoll((char *)token->token_data, &endptr, 10);
			if(errno != 0) {
				printf("Only Integers Supported, Using 0 For Now!!!\n\n");
				value = 0;
			}

			if(*endptr != '\0') {
				printf("Error!!! Invalid Value!!!\n\n");

				root_expression->is_complete = false;

				return incomplete_expression;
			}

			ValueToken *val = create_value_token(VALUE_TOKEN_TYPE_INTEGER, value);
			if(val == NULL) {
				printf("Error!!! Failed To Create Value!!!\n\n");

				root_expression->is_complete = false;

				return incomplete_expression;
			}

			ExpressionElement *element = create_expression_element(ELEMENT_VALUE, val);
			if(element == NULL) {
				printf("Error!!! Failed To Create Value Element!!!\n\n");

				root_expression->is_complete = false;

				free_value_token(val);
				return incomplete_expression;
			}

			Expression *current_expression = stack_peek(expression_stack);
			if(append_to_expression(current_expression, element) != 0) {
				printf("Error!!! Failed To Append Value Element!!!\n\n");

				root_expression->is_complete = false;

				free_expression_element(element);
				return incomplete_expression;
			}
		} else {
			printf("Error!!! Unrecognized Token Type!!!\n\n");

			root_expression->is_complete = false;

			return incomplete_expression;
		}
	}

	root_expression = collect_expression_stack(expression_stack);

	free_stack(expression_stack);
	return root_expression;
}

ExpressionElement *create_expression_element_from_token(Token *token)
{
	if(token == NULL) {
		return NULL;
	}

	ExpressionElement *element = (ExpressionElement *)malloc(sizeof(ExpressionElement));
	if(element == NULL) {
		printf("Error!!! Failed To Allocate Memory For Expression Element!!!\n\n");

		return NULL;
	}

	if(token->token_type == 'V') {                                                       // обрабатываем значение
		element->expression_element_type = ELEMENT_VALUE;

		element->value.value_data = malloc(sizeof(long long));

		if(element->value.value_data == NULL) {
			printf("Error!!! Failed To Allocate Memory For Value Data!!!\n\n");

			free(element);
			return NULL;
		}

		*(long long *)element->value.value_data = atoi((char *)token->token_data);
	} else if(token->token_type == 'S') {                                                // обрабатываем символ
		if(token->token_data == NULL) {
			printf("Error!!! Token Data Is NULL!!!\n\n");

			free(element);
			return NULL;
		}

		element->expression_element_type = ELEMENT_SYMBOL;

		element->symbol.symbol_name = strdup((char *)token->token_data);

		if(element->symbol.symbol_name == NULL) {
			printf("Error!!! Failed To Duplicate String For Symbol Name!!!\n\n");

			free(element);
			return NULL;
		}
	} else if(token->token_type == 'L' || token->token_type == 'R') {                    // обрабатываем скобки
		element->expression_element_type = ELEMENT_SYMBOL;

		if(token->token_type == 'L') {
			element->symbol.symbol_name = strdup("(");
		} else {
			element->symbol.symbol_name = strdup(")");
		}

		if(element->symbol.symbol_name == NULL) {
			printf("Error!!! Failed To Duplicate String For Symbol Name!!!\n\n");

			free(element);
			return NULL;
		}
	} else {
		printf("Error!!! Unrecognized Token Type!!!\n\n");

		free(element);
		return NULL;
	}

	return element;
}
