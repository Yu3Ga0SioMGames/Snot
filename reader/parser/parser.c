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

	expression->element = NULL;

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
	}

	free(symbol);
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

	if(expression->element != NULL) {
		free_node(expression->element);
	}

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

Expression *append_to_expression(Expression *expression, Node *input_element)
{
	if(expression == NULL) {
		return NULL;
	}

	expression->element = input_element;

	return expression;
}
