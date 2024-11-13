#include "list.h" // включаем заголовочный файл

/// Функция создания нового списка:
List *create_list()
{
	List *list = (List *)malloc(sizeof(List));                        // выделяем память для нового списка
	if(list == NULL) {                                                // проверяем, успешно ли выделена память
		return NULL;
	}

	list->length = 0;                                                 // инициализируем длину списка
	list->first = NULL;                                               // устанавливаем первый узел на "NULL"
	list->last = NULL;                                                // устанавливаем последний узел на "NULL"

	/// Инициализируем таблицу методов списка:
	list->mtbl.print = (print_ptr)print_list;
	list->mtbl.append = (append_ptr)append_to_list;
	list->mtbl.length = (length_ptr)list_length;
	list->mtbl.prepend = (prepend_ptr)prepend_to_list;
	list->mtbl.insert = (insert_ptr)insert_to_list;
	list->mtbl.delete = (delete_ptr)delete_from_list;
	list->mtbl.get = (get_ptr)get_from_list;

	return list;
}

/// Функция получения длины списка:
size_t list_length(List *list)
{
	if(list == NULL) {                                                // проверяем, не является ли список "NULL"
		return 0;
	}

	return list->length;                                              // возвращаем длину списка
}

/// Функция освобождения памяти списка:
void free_list(List *list)
{
	if(list == NULL) {                                                // проверяем, не является ли список "NULL"
		return;
	}

	/// Освобождаем память каждого узла:
	while(list->last != NULL) {
		list->last = list->first->next;
		free_node(list->first);
		list->first = list->last;
	}

	free(list);                                                       // освобождаем память самого списка
}

/// Функция создания нового узла:
Node *create_node(LIST_DATA_TYPE input_data)
{
	Node *node = (Node *)malloc(sizeof(Node));                        // выделяем память для нового узла
	if(node == NULL) {                                                // проверяем, успешно ли выделена память
		return NULL;
	}

	node->data = input_data;                                          // присваиваем данные узлу
	node->next = NULL;                                                // следующий узел устанавливаем на "NULL"

	return node;
}

/// Функция освобождения памяти узла:
void free_node(Node *input_node)
{
	free(input_node);                                                 // освобождаем память узла
}

/// Функция добавления элемента в конец списка:
int append_to_list(List *list, LIST_DATA_TYPE data)
{
	if(list == NULL) {                                                // проверяем, не является ли список "NULL"
		return NO_LIST_ERROR;
	}

	Node *new_node = create_node(data);                               // создаем новый узел
	if(new_node == NULL) {                                            // проверяем, успешно ли создан новый узел
		return ND_CREATE_ERROR;
	}

	if(0 == list->length) {                                           // если список пуст
		list->first = new_node;
		list->last = new_node;
	} else {                                                          // если в списке уже есть элементы
		list->last->next = new_node;
		list->last = new_node;
	}

	list->length++;                                                   // увеличиваем длину списка

	return 0;
}

/// Функция печати элементов списка:
void print_list(List *list)
{
	if(list == NULL) {                                                // проверяем, не является ли список "NULL"
		return;
	}

	Node *temp = list->first;                                         // начинаем с первого узла
	while(temp != NULL) {                                             // пока не дойдем до конца списка
		printf("%lld ", temp->data);
		temp = temp->next;
	}

	printf("\n");                                                     // добавляем перевод строки после печати списка
}

/// Функция получения узла списка по индексу:
Node *get_node_from_list(Node *start_node, size_t index)
{
	Node *current_node = start_node;                                  // начинаем с указанного узла

	for(; index != 0 && current_node != NULL; --index) {              // перемещаемся к нужному узлу
		current_node = current_node->next;
	}

	return current_node;
}

/// Функция получения данных из списка по индексу:
int get_from_list(List *list, size_t index, LIST_DATA_TYPE *return_value)
{
	if(list == NULL) {                                                // проверяем, не является ли список "NULL"
		return NO_LIST_ERROR;
	}

	if(index >= list->length) {                                       // проверяем, не выходит ли индекс за пределы списка
		return BAD_POS_ERROR;
	}

	Node *node_ptr = get_node_from_list(list->first, index);          // получаем узел по индексу
	*return_value = node_ptr->data;                                   // возвращаем данные узла

	return 0;
}

/// Функция вставки элемента в список по индексу:
int insert_to_list(List *list, size_t index, LIST_DATA_TYPE data)
{
	if(list == NULL) {                                                // проверяем, не является ли список "NULL"
		return NO_LIST_ERROR;
	}

	if(index == 0) {                                                  // если индекс равен '0', добавляем в начало списка
		return prepend_to_list(list, data);
	}

	Node *new_node = create_node(data);                               // создаем новый узел
	if(new_node == NULL) {                                            // проверяем, успешно ли создан новый узел
		return ND_CREATE_ERROR;
	}

	if((index - 1) >= list->length) {                                 // проверяем, не выходит ли индекс за пределы списка
		return BAD_POS_ERROR;
	}

	Node *prev_node = get_node_from_list(list->first, index - 1);     // получаем узел, предшествующий указанному индексу

	new_node->next = prev_node->next;                                 // связываем новый узел с последующим
	prev_node->next = new_node;                                       // связываем предшествующий узел с новым

	if(index == list->length) {                                       // обновляем указатель на последний узел, если добавляем в конец
		list->last = new_node;
	}

	list->length++;                                                   // увеличиваем длину списка

	return 0;
}

/// Функция добавления элемента в начало списка:
int prepend_to_list(List *list, LIST_DATA_TYPE data)
{
	if(list == NULL) {                                                // проверяем, не является ли список NULL
		return NO_LIST_ERROR;
	}

	Node *new_node = create_node(data);                               // создаем новый узел
	if(new_node == NULL) {                                            // проверяем, успешно ли создан новый узел
		return ND_CREATE_ERROR;
	}

	if(0 != list->length) {                                           // если в списке уже есть элементы
		new_node->next = list->first;
		list->first = new_node;
	} else {                                                          // если список пуст
		list->first = new_node;
		list->last = new_node;
	}

	list->length++;                                                   // увеличиваем длину списка

	return 0;
}

/// Функция удаления элемента из списка по индексу:
int delete_from_list(List *list, size_t index)
{
	if(list == NULL) {                                                // проверяем, не является ли список "NULL"
		return NO_LIST_ERROR;
	}

	if(index >= list->length) {                                       // проверяем, не выходит ли индекс за пределы списка
		return BAD_POS_ERROR;
	}

	Node *current_node;
	if(index == 0) {                                                  // если удаляем первый элемент списка
		current_node = list->first;
		list->first = list->first->next;

		if(1 == list->length) {                                       // если список состоял из одного элемента
			list->last = NULL;
		}
	} else {
		Node *prev_node = get_node_from_list(list->first, index - 1); // получаем узел, предшествующий указанному индексу
		if(index == (list->length - 1)) {                             // если удаляем последний элемент списка
			list->last = prev_node;
		}

		current_node = prev_node->next;
		prev_node->next = current_node->next;
	}

	free_node(current_node);                                          // освобождаем память удаленного узла

	list->length--;                                                   // уменьшаем длину списка

	return 0;
}
