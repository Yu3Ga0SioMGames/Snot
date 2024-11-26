#ifndef EVALUATOR_H_INCLUDED
#define EVALUATOR_H_INCLUDED

#include "../libmap/map.h"
#include "../main_common.h"
#include "../reader/reader.h"
#include "../reader/parser/parser.h"

#define VALUE_TYPE_NIL 0
#define VALUE_TYPE_CHAR 1
#define VALUE_TYPE_DOUBLE 2
#define VALUE_TYPE_INTEGER 3

extern map *variables;

typedef
struct _value
{
	uint64_t value_type;
	void *value;
} Value;

void free_value(Value *);

Value *eval(ExpressionElement *);

Value *eval_symbol(Symbol *);
Value *eval_value(ValueToken *);
Value *eval_funcall(Expression *);
Value *eval_special(Expression *);
Value *eval_expression(Expression *);

Value *eval_special_if(Expression *);
Value *eval_special_def(Expression *);
Value *eval_special_block(Expression *);

Value *create_value(uint64_t value_type, void *value_data);

#endif // EVALUATOR_H_INCLUDED
