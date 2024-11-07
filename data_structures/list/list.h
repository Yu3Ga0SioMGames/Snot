#ifndef LIST_H_INCLUDED


#define LIST_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../container/container.h"


#define ND_CREATE_ERROR 1
#define BAD_POS_ERROR (ND_CREATE_ERROR + 1)
#define NO_LIST_ERROR (BAD_POS_ERROR + 1)


typedef
struct _node
{
	void *data;
	struct _node *next;
} Node;

typedef
struct
{
	ContainerMTable mtbl;
	size_t length;
	Node *first;
	Node *last;
} List;


List *create_list();

void free_list(List *);
void free_node(Node *);
void print_list(List *);

size_t list_length(List *);

Node *create_node(void *);
Node *get_node_from_list(Node *, size_t);

int append_to_list(List *, int64_t);
int delete_from_list(List *, size_t);
int prepend_to_list(List *, int64_t);
int insert_to_list(List *, size_t, int64_t);
int get_from_list(List *, size_t, int64_t *);


#endif
