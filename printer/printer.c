#include "printer.h"

void print_value(const Value *value)
{
	if(value == NULL) {
		printf("Value Is (\"NULL\")!!!\n\n");

		return;
	}

	switch(value->value_type) {
	case VALUE_TYPE_NIL:
		printf("NIL\n");

		break;
	case VALUE_TYPE_CHAR:
		printf("%s\n", *(char *)value->value);

		break;
	case VALUE_TYPE_DOUBLE:
		printf("%lf\n", *(double *)value->value);

		break;
	case VALUE_TYPE_INTEGER:
		printf("%d\n", (int)(value->value));

		break;
	default:
		printf("Unknown Value Type!!!\n");

		break;
	}
}
