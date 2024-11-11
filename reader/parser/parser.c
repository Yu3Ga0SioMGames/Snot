#include "parser.h"

Symbol *create_symbol(char *input_name)
{
	Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
	if(symbol == NULL) {
		return NULL;
	}

	if(input_name == NULL) {
		symbol->symbol_name = NULL;
	}

	symbol->symbol_name = strdup(input_name);

	return symbol;
}

Value *create_value(uint64_t input_type, void *input_data)
{
	Value *value = (Value *)malloc(sizeof(Value));
	if(value == NULL) {
		return NULL;
	}

	value->value_type = input_type;
	value->value_data = input_data;

	return value;
}

Expression *create_expression()
{
	Expression *expression = (Expression *)malloc(sizeof(Expression));
	if(expression == NULL) {
		return NULL;
	}

	expression->element_list = create_list();
	if(expression->element_list == NULL) {
		free(expression);
		return NULL;
	}

	return expression;
}

ExpressionElement *create_expression_element(uint64_t input_expression_element_type, void *input_data)
{
	ExpressionElement *element = (ExpressionElement *)malloc(sizeof(ExpressionElement));
	if(element == NULL) {
		return NULL;
	}

	element->expression_element_type = input_expression_element_type;
	switch(input_expression_element_type) {
	case ELEMENT_SYMBOL:
		element->symbol = *((Symbol *)input_data);
		break;
	case ELEMENT_VALUE:
		element->value = *((Value *)input_data);
		break;
	case ELEMENT_EXPRESSION:
		element->expression = *((Expression *)input_data);
		break;
	}

	return element;
}

void free_symbol(Symbol *symbol)
{
	if(symbol == NULL) {
		return;
	}

	if(symbol->symbol_name != NULL) {
		free(symbol->symbol_name);
		symbol->symbol_name = NULL;
	}

	free(symbol);
	symbol = NULL;
}

void free_value(Value *value)
{
	if(value == NULL) {
		return;
	}

	if(value->value_data != NULL) {
		free(value->value_data);
	}

	free(value);
}

void free_expression(Expression *expression)
{
	if(expression == NULL) {
		return;
	}

	free_list(expression->element_list);
	free(expression);
}

void free_expression_element(ExpressionElement *element)
{
	if(element == NULL) {
		return;
	}

	switch(element->expression_element_type) {
	case ELEMENT_SYMBOL:
		free_symbol(&(element->symbol));
		break;
	case ELEMENT_VALUE:
		free_value(&(element->value));
		break;
	case ELEMENT_EXPRESSION:
		free_expression(&(element->expression));
		break;
	}

	free(element);
}

int append_to_expression(Expression *expression, ExpressionElement *element)
{
	return append_to_list(expression->element_list, element);
}

Expression *parse(Token **converted_tokens, size_t token_count)
{
	Stack *expression_stack = create_stack();
	if(expression_stack == NULL) {
		return NULL;
	}

	Expression *root_expression = create_expression();
	if(root_expression == NULL) {
		free_stack(expression_stack);
		return NULL;
	}

	Expression *current_expression = root_expression;

	for(size_t i = 0; i < token_count; ++i) {
		Token *token = converted_tokens[i];

		if(token->token_type == 'L') {
			stack_push(expression_stack, current_expression);
			current_expression = create_expression();

			if(current_expression == NULL) {
				free_stack(expression_stack);
				return NULL;
			}
		} else if(token->token_type == 'R') {
			if(expression_stack->stack_size == 0) {
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}

			Expression *prev_expression = stack_pop(expression_stack);
			if(prev_expression == NULL) {
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}

			ExpressionElement *element = create_expression_element(ELEMENT_EXPRESSION, current_expression);
			if(element == NULL) {
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}

			if(append_to_expression(prev_expression, element) != 0) {
				free_expression_element(element);
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}

			current_expression = prev_expression;
		} else if(token->token_type == 'S') {
			Symbol *symbol = create_symbol((char *)token->token_data);
			if(symbol == NULL) {
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}

			ExpressionElement *element = create_expression_element(ELEMENT_SYMBOL, symbol);
			if(element == NULL) {
				free_symbol(symbol);
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}

			if(append_to_expression(current_expression, element) != 0) {
				free_expression_element(element);
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}
		} else if(token->token_type == 'V') {
			int value = atoi((char *)token->token_data);                 // преобразуем строку в число
			Value *val = create_value(sizeof(int), malloc(sizeof(int))); // создаем новое значение с выделенной памятью
			if(val == NULL) {
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}

			*(int *)(val->value_data) = value;                           // сохраняем значение по указателю

			ExpressionElement *element = create_expression_element(ELEMENT_VALUE, val);
			if(element == NULL) {
				free_value(val);
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}

			if(append_to_expression(current_expression, element) != 0) {
				free_expression_element(element);
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}
		}
	}

	if(expression_stack->stack_size != 0) {
		free_expression(current_expression);
		free_stack(expression_stack);
		return NULL;
	}

	free_stack(expression_stack);
	return root_expression;
}

Expression *parse2(Token **converted_tokens, size_t token_count)
{
	Stack *expression_stack = create_stack();
	if(expression_stack == NULL) {
		return NULL;
	}

	Expression *root_expression = create_expression();
	if(root_expression == NULL) {
		free_stack(expression_stack);
		return NULL;
	}

	stack_push(expression_stack, root_expression);

	for(size_t i = 0; i < token_count; ++i) {
		Token *token = converted_tokens[i];

		if(token->token_type == 'L') {
			Expression *new_expression = create_expression();
			if(new_expression == NULL) {
				free_stack(expression_stack);
				return NULL;
			}

			stack_push(expression_stack, new_expression);
		} else if(token->token_type == 'R') {
			if(expression_stack->stack_size < 2) {
				free_stack(expression_stack);
				return NULL;
			}

			Expression *current_expression = stack_pop(expression_stack);

			Expression *parent_expression = stack_peek(expression_stack);

			ExpressionElement *element = create_expression_element(ELEMENT_EXPRESSION, current_expression);
			if(element == NULL) {
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}

			if(append_to_expression(parent_expression, element) != 0) {
				free_expression_element(element);
				free_expression(current_expression);
				free_stack(expression_stack);
				return NULL;
			}
		} else if(token->token_type == 'S') {
			Symbol *symbol = create_symbol((char *)token->token_data);
			if(symbol == NULL) {
				free_stack(expression_stack);
				return NULL;
			}

			ExpressionElement *element = create_expression_element(ELEMENT_SYMBOL, symbol);
			if(element == NULL) {
				free_symbol(symbol);
				free_stack(expression_stack);
				return NULL;
			}

			Expression *current_expression = stack_peek(expression_stack);
			if(append_to_expression(current_expression, element) != 0) {
				free_expression_element(element);
				free_stack(expression_stack);
				return NULL;
			}
		} else if(token->token_type == 'V') {
			int value = atoi((char *)token->token_data);
			Value *val = create_value(sizeof(int), malloc(sizeof(int)));
			if(val == NULL) {
				free_stack(expression_stack);
				return NULL;
			}

			*(int *)(val->value_data) = value;

			ExpressionElement *element = create_expression_element(ELEMENT_VALUE, val);
			if(element == NULL) {
				free_value(val);
				free_stack(expression_stack);
				return NULL;
			}

			Expression *current_expression = stack_peek(expression_stack);
			if(append_to_expression(current_expression, element) != 0) {
				free_expression_element(element);
				free_stack(expression_stack);
				return NULL;
			}
		}
	}

	if(expression_stack->stack_size != 1) {
		free_stack(expression_stack);
		return NULL;
	}

	Expression *root_expression_result = stack_pop(expression_stack);
	free_stack(expression_stack);
	return root_expression_result;
}

void print_expression(Expression * expression, int8_t depth)
{
	if(expression == NULL) {
		return;
	}

	Node *current = expression->element_list->first;

	while(current != NULL) {
		ExpressionElement *element = (ExpressionElement *)current->data;

		for(int i = 0; i < depth; ++i) {
			printf("  ");
		}

		switch(element->expression_element_type) {
		case ELEMENT_SYMBOL:
			printf("Symbol: %s\n", element->symbol.symbol_name);
			break;
		case ELEMENT_VALUE:
			printf("Value: %lld\n", *(int *)element->value.value_data);
			break;
		case ELEMENT_EXPRESSION:
			printf("Expression:\n");
			print_expression(&element->expression, ++depth);
			break;
		}

		current = current->next;
	}
}
