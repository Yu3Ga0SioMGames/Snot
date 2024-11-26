#ifndef CONTAINER_H_INCLUDED                           // проверяем, чтобы содержимое файла не было включено более одного раза

#define CONTAINER_H_INCLUDED                           // определяем макрос, предотвращающего повторного включения содержимого файла


#include <stddef.h>                                    // файл для определения типов и макросов
#include <stdint.h>                                    // файл для определения типов с фиксированным размером


typedef void* Container;                               // определяем тип "Container", как указателя на "void"
typedef void (*print_ptr)(Container);                  // определяем тип указателя на функцию для печати контейнера
typedef size_t (*length_ptr)(Container);               // определяем тип указателя на функцию для получения длины контейнера
typedef int (*delete_ptr)(Container, size_t);          // определяем тип указателя на функцию для удаления элемента из контейнера
typedef int (*append_ptr)(Container, int64_t);         // определяем тип указателя на функцию для добавления элемента в конец контейнера
typedef int (*prepend_ptr)(Container, int64_t);        // определяем тип указателя на функцию для добавления элемента в начало контейнера
typedef int (*get_ptr)(Container, size_t, int64_t *);  // определяем тип указателя на функцию для получения элемента из контейнера
typedef int (*insert_ptr)(Container, size_t, int64_t); // определяем тип указателя на функцию для вставки элемента в контейнер


typedef
struct _container_m_table                              // определяем структуру для методной таблицы контейнера
{
	print_ptr print;                                   // указатель на функцию печати
	length_ptr length;                                 // указатель на функцию получения длины контейнера
	append_ptr append;                                 // указатель на функцию добавления элемента в конец контейнера
	prepend_ptr prepend;                               // указатель на функцию добавления элемента в начало контейнера
	insert_ptr insert;                                 // указатель на функцию вставки элемента в контейнер
	delete_ptr delete;                                 // указатель на функцию удаления элемента из контейнера
	get_ptr get;                                       // указатель на функцию получения элемента из контейнера
} ContainerMTable;                                     // объявляем структуру "ContainerMTable"


void print(Container obj);                             // объявляем функцию печати контейнера

size_t length(Container obj);                          // объявляем функцию получения длины контейнера

int append(Container obj, int64_t data);               // объявляем функцию добавления элемента в конец контейнера
int delete(Container obj, size_t index);               // объявляем функцию удаления элемента из контейнера
int prepend(Container obj, int64_t data);              // объявляем функцию добавления элемента в начало контейнера
int get(Container obj, size_t index, int64_t *rv);     // объявляем функцию получения элемента из контейнера
int insert(Container obj, size_t index, int64_t data); // объявляем функцию вставки элемента в контейнер


#endif                                                 // завершаем условное включения файла
