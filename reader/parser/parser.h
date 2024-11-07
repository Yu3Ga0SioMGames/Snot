#ifndef PARSER_H_INCLUDED

#define PARSER_H_INCLUDED


#include "../../data_structures/list/list.h"


#define ELEMENT_SYMBOL 0
#define ELEMENT_VALUE 1
#define ELEMENT_EXPRESSION 2


typedef
struct _symbol
{
	char *symbol_name;
} Symbol;

typedef
struct _value
{
	uint64_t value_type;
	void *value_data;
} Value;

typedef
struct _expression
{
	Node *element;
} Expression;

typedef
struct _expression_element
{
	uint64_t expression_element_type;
	union {
		Symbol symbol;
		Value value;
		Expression expression;
	};
} ExpressionElement;


void free_value(Value *);
void free_symbol(Symbol *);
void free_expression(Expression *);
void free_expression_element(ExpressionElement *);

Expression *create_expression();
Expression *append_to_expression(Expression *, Node *);

Symbol *create_symbol(char *);
Value *create_value(uint64_t, void *);
ExpressionElement *create_expression_element(uint64_t, void *);


#endif
