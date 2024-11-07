#include "list.h"

List *create_list()
{
	List *list = (List *)malloc(sizeof(List));
	if(list == NULL) {
		return NULL;
	}

	list->length = 0;
	list->first = NULL;
	list->last = NULL;

	list->mtbl.print = (print_ptr)print_list;
	list->mtbl.append = (append_ptr)append_to_list;
	list->mtbl.length = (length_ptr)list_length;
	list->mtbl.prepend = (prepend_ptr)prepend_to_list;
	list->mtbl.insert = (insert_ptr)insert_to_list;
	list->mtbl.delete = (delete_ptr)delete_from_list;
	list->mtbl.get = (get_ptr)get_from_list;
	return list;
}

void free_list(List *list)
{
	if(list == NULL) {
		return;
	}

	while(list->last == NULL) {
		list->last = list->first->next;
		free_node(list->first);
		list->first = list->last;
	}

	free(list);
}

Node *create_node(void *input_data)
{
	Node *node = (Node *)malloc(sizeof(Node));
	if(node == NULL) {
		return NULL;
	}

	node->data = input_data;
	node->next = NULL;

	return node;
}

void free_node(Node *input_node)
{
	free(input_node);
}

int append_to_list(List *list, int64_t data)
{
	if(list == NULL) {
		return NO_LIST_ERROR;
	}

	Node *new_node = create_node(data);
	if(new_node == NULL) {
		return ND_CREATE_ERROR;
	}

	if(0 == list->length) {
		list->first = new_node;
		list->last = new_node;
	} else {
		list->last->next = new_node;
		list->last = new_node;
	}

	list->length++;

	return 0;
}

void print_list(List *list)
{
	if(list == NULL) {
		return;
	}

	Node *temp = list->first;
	while(temp != NULL) {
		printf("%lld ", temp->data);
		temp = temp->next;
	}

	printf("\n");
}

Node *get_node_from_list(Node *start_node, size_t index)
{
	Node *current_node = start_node;

	for(; index != 0 && current_node != NULL; --index) {
		current_node = current_node->next;
	}

	return current_node;
}

int get_from_list(List *list, size_t index, int64_t *return_value)
{
	if(list == NULL) {
		return NO_LIST_ERROR;
	}

	if(index >= list->length) {
		return BAD_POS_ERROR;
	}

	Node *node_ptr = get_node_from_list(list->first, index);
	*return_value = node_ptr->data;

	return 0;
}

int insert_to_list(List *list, size_t index, int64_t data)
{
	if(list == NULL) {
		return NO_LIST_ERROR;
	}

	if(index == 0) {
		return prepend_to_list(list, data);
	}

	Node *new_node = create_node(data);
	if(new_node == NULL) {
		return ND_CREATE_ERROR;
	}

	if((index - 1) >= list->length) {
		return BAD_POS_ERROR;
	}

	Node *prev_node = get_node_from_list(list->first, index - 1);

	new_node->next = prev_node->next;
	prev_node->next = new_node;

	if(index == list->length) {
		list->last = new_node;
	}

	list->length++;

	return 0;
}

int prepend_to_list(List *list, int64_t data)
{
	if(list == NULL) {
		return NO_LIST_ERROR;
	}

	Node *new_node = create_node(data);
	if(new_node == NULL) {
		return ND_CREATE_ERROR;
	}

	if(0 != list->length) {
		new_node->next = list->first;
		list->first = new_node;
	} else {
		list->first = new_node;
		list->last = new_node;
	}

	list->length++;

	return 0;
}

int delete_from_list(List *list, size_t index)
{
	if(list == NULL) {
		return NO_LIST_ERROR;
	}

	if(index >= list->length) {
		return BAD_POS_ERROR;
	}

	Node *current_node;
	if(index == 0) {
		current_node = list->first;
		list->first = list->first->next;

		if(1 == list->length) {
			list->last = NULL;
		}
	} else {
		Node *prev_node = get_node_from_list(list->first, index - 1);
		if(index == (list->length - 1)) {
			list->last = prev_node;
		}

		current_node = prev_node->next;
		prev_node->next = current_node->next;
	}

	free_node(current_node);

	list->length--;

	return 0;
}

size_t list_length(List *list)
{
	if(list == NULL) {
		return 0;
	}

	return list->length;
}
