#include "evaluator.h"

map *variables;

Value *create_value(uint64_t value_type, void *value_data)
{
	Value *value = (Value *)malloc(sizeof(Value *));
	if(value == NULL) {
		return NULL;
	}

	value->value_type = value_type;
	value->value = value_data;

	return value;
}

Value *create_integer_value(int value_data)
{
	return create_value(VALUE_TYPE_INTEGER, (void *)value_data);
}

void free_value(Value *value)
{
	if(value->value_type == VALUE_TYPE_INTEGER) {
		free(value);
	}
}

Value *eval_value(ValueToken *val)
{
	return create_integer_value(val->value_data);
}

Value *eval_symbol(Symbol *expression)
{
	if(expression == NULL) {
		return NULL;
	}

	if(map_contains(variables, expression->symbol_name)) {
		return map_get(variables, expression->symbol_name);
	}

	return create_value(VALUE_TYPE_NIL, NULL);
}

Value *eval_expression(Expression *expression)
{
	if(expression == NULL) {
		return NULL;
	}

	Value **values = (Value **)malloc(expression->element_list->length * sizeof(Value *));

	ExpressionElement *first_element = NULL;
	int rc = (ExpressionElement *)get_from_list(expression->element_list, 0, &first_element);
	if(first_element->expression_element_type == ELEMENT_SYMBOL) {
		Value *result_special = eval_special(expression);
		if(result_special != NULL) {
			return result_special;
		}
	}

	for(size_t i = 0; i < expression->element_list->length; ++i) {
		ExpressionElement *expression_element = NULL;

		int rc = get_from_list(expression->element_list, i, &expression_element);
		if(rc != 0) {
			return NULL;
		}

		values[i] = eval(expression_element);
	}

	// если первый элемент - это имя специальной формы, то вычислить специальную форму
	// values[0] должно содержать функцию, все остальное должно содержать элементы

	return *values;
}

Value *eval(ExpressionElement *expression)
{
	if(expression == NULL) {
		return NULL;
	}

	switch(expression->expression_element_type) {
	case ELEMENT_SYMBOL:
		return eval_symbol(&(expression->symbol));
	case ELEMENT_VALUE:
		return eval_value(&(expression->value));
	case ELEMENT_EXPRESSION:
		return eval_expression(&(expression->expression));
	default:
		return NULL;
	}

	return NULL;
}

Value *eval_special(Expression *expr)
{
	if(expr == NULL) {
		return NULL;
	}

	ExpressionElement *first_element = NULL;
	int rc = get_from_list(expr->element_list, 0, &first_element);
	if(first_element == NULL) {
		return NULL;
	}

	if(first_element->expression_element_type != ELEMENT_SYMBOL) {
		return NULL;
	}

	Symbol *sym = &(first_element->symbol);
	if(strncmp(sym->symbol_name, "if", 3) == 0) {
		return eval_special_if(expr);
	}

	if(strncmp(sym->symbol_name, "def", 4) == 0) {
		return eval_special_def(expr);
	}

	if(strncmp(sym->symbol_name, "block", 6) == 0) {
		return eval_special_block(expr);
	}

	return NULL;
}


Value *eval_special_if(Expression *expr)
{
	return NULL;
}

Value *eval_special_def(Expression *expr)
{
	/// (def name value):
	List *element_list = expr->element_list;

	ExpressionElement *var_name = NULL;
	int rc = get_from_list(element_list, 1, &var_name);

	ExpressionElement *var_value_element = NULL;
	rc = get_from_list(element_list, 2, &var_value_element);

	Value *var_value = eval(var_value_element);

	if(var_name != NULL && var_value != NULL) {
		if(var_name->expression_element_type == ELEMENT_SYMBOL) {
			map_set(variables, var_name->symbol.symbol_name, var_value);
		}
	}

	return var_value;
}

Value *eval_special_block(Expression *expr)
{
	return NULL;
}
