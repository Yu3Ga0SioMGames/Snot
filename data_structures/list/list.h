#ifndef LIST_H_INCLUDED

/// Начало:

#define LIST_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../container/container.h" // включаем заголовочный файл контейнера


/// Определяем коды ошибок:
#define ND_CREATE_ERROR 1
#define BAD_POS_ERROR (ND_CREATE_ERROR + 1)
#define NO_LIST_ERROR (BAD_POS_ERROR + 1)

#define LIST_DATA_TYPE void *

/// Структура узла списка:
typedef
struct _node
{
	LIST_DATA_TYPE data;
	struct _node *next;
} Node;

/// Структура самого списка:
typedef
struct _list
{
	ContainerMTable mtbl;           // таблица методов для контейнера
	size_t length;                  // длина списка
	Node *first;                    // указатель на первый узел
	Node *last;                     // указатель на последний узел
} List;


/// Прототипы функций для работы со списком:
List *create_list();

void free_list(List *);
void free_node(Node *);
void print_list(List *);

size_t list_length(List *);

Node *create_node(LIST_DATA_TYPE);
Node *get_node_from_list(Node *, size_t);

int append_to_list(List *, LIST_DATA_TYPE);
int delete_from_list(List *, size_t);
int prepend_to_list(List *, LIST_DATA_TYPE);
int insert_to_list(List *, size_t, LIST_DATA_TYPE);
int get_from_list(List *, size_t, LIST_DATA_TYPE *);


#endif                               // конец
