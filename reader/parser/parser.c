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

int append_to_expression(Expression *expression, ExpressionElement *input_element)
{
	if(expression == NULL) {
		return NO_LIST_ERROR;
	}

	return append_to_list(expression->element_list, input_element);
}

Expression *parse(Token **tokens, size_t token_count)
{
	Stack *stack = create_stack();
	if(stack == NULL) {
		return NULL;
	}

	Expression *root_expression = create_expression();
	if(root_expression == NULL) {
		free_stack(stack);
		return NULL;
	}

	for(size_t i = 0; i < token_count; ++i) {
		Token *token = tokens[i];

		if(token->token_type == 'LP') {
			stack_push(stack, root_expression);
			root_expression = create_expression();
			if(root_expression == NULL) {
				free_stack(stack);
				return NULL;
			}
		} else if(token->token_type == 'RP') {
			if(stack->stack_size == 0) {
				free_expression(root_expression);
				free_stack(stack);
				return NULL;
			}

			Expression *prev_expression = stack_pop(stack);
			if(prev_expression == NULL) {
				free_expression(root_expression);
				free_stack(stack);
				return NULL;
			}

			ExpressionElement *element = create_expression_element(ELEMENT_EXPRESSION, root_expression);
			if(element == NULL) {
				free_expression(root_expression);
				free_stack(stack);
				return NULL;
			}

			if(append_to_expression(prev_expression, element) != 0) {
				free_expression_element(element);
				free_expression(root_expression);
				free_stack(stack);
				return NULL;
			}

			root_expression = prev_expression;
		} else if(token->token_type == 'SYM') {
			Symbol *symbol = create_symbol((char *)token->token_data);
			if(symbol == NULL) {
				free_expression(root_expression);
				free_stack(stack);
				return NULL;
			}

			ExpressionElement *element = create_expression_element(ELEMENT_SYMBOL, symbol);
			if(element == NULL) {
				free_symbol(symbol);
				free_expression(root_expression);
				free_stack(stack);
				return NULL;
			}

			if(append_to_expression(root_expression, element) != 0) {
				free_expression_element(element);
				free_expression(root_expression);
				free_stack(stack);
				return NULL;
			}
		} else if(token->token_type == 'VAL') {
			int value = atoi((char *)token->token_data);
			Value *val = create_value(value, NULL);
			if(val == NULL) {
				free_expression(root_expression);
				free_stack(stack);
				return NULL;
			}

			ExpressionElement *element = create_expression_element(ELEMENT_VALUE, val);
			if(element == NULL) {
				free_value(val);
				free_expression(root_expression);
				free_stack(stack);
				return NULL;
			}

			if(append_to_expression(root_expression, element) != 0) {
				free_expression_element(element);
				free_expression(root_expression);
				free_stack(stack);
				return NULL;
			}
		}
	}

	if(stack->stack_size != 0) {
		free_expression(root_expression);
		free_stack(stack);
		return NULL;
	}

	free_stack(stack);
	return root_expression;
}
