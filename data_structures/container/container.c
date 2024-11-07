/*
    Смысл и принцип работы функции:
        1.) Данные функции являются частью системы виртуальных методов для контейнерного объекта;
        2.) Используя таблицу методов(Методную таблицу), они вызывают соответствующие методы контейнера;
*/
#include "container.h"                                // подключаем заголовочный файл "container.h"

void print(Container obj)                             // функция "print" для печати содержимого контейнера
{
	ContainerMTable *table = (ContainerMTable *)obj;  // преобразуем контейнерный объект в указатель на таблицу методов контейнера
	(table->print)(obj);                              // вызываем метод "print" из таблицы методов контейнера
}

int append(Container obj, int64_t data)               // функция "append" для добавления данных в конец контейнера
{
	ContainerMTable *table = (ContainerMTable *)obj;  // преобразуем контейнерный объект в указатель на таблицу методов контейнера
	return (table->append)(obj, data);                // вызываем метод "append" из таблицы методов контейнера и возвращаем результат
}

size_t length(Container obj)                          // функция "length" для получения длины контейнера
{
	ContainerMTable *table = (ContainerMTable *)obj;  // преобразуем контейнерный объект в указатель на таблицу методов контейнера
	return (table->length)(obj);                      // вызываем метод "length" из таблицы методов контейнера и возвращаем результат
}

int prepend(Container obj, int64_t data)              // функция "prepend" для добавления данных в начало контейнера
{
	ContainerMTable *table = (ContainerMTable *)obj;  // преобразуем контейнерный объект в указатель на таблицу методов контейнера
	return (table->prepend)(obj, data);               // вызываем метод "prepend" из таблицы методов контейнера и возвращаем результат
}

int insert(Container obj, size_t index, int64_t data) // функция "insert" для вставки данных в контейнер на заданную позицию
{
	ContainerMTable *table = (ContainerMTable *)obj;  // преобразуем контейнерный объект в указатель на таблицу методов контейнера
	return (table->insert)(obj, index, data);         // вызываем метод "insert" из таблицы методов контейнера и возвращаем результат
}

int delete(Container obj, size_t index)               // функция "delete" для удаления данных из контейнера на заданной позиции
{
	ContainerMTable *table = (ContainerMTable *)obj;  // преобразуем контейнерный объект в указатель на таблицу методов контейнера
	return (table->delete)(obj, index);               // вызываем метод "delete" из таблицы методов контейнера и возвращаем результат
}

int get(Container obj, size_t index, int64_t *rv)     // функция "get" для получения данных из контейнера на заданной позиции
{
	ContainerMTable *table = (ContainerMTable *)obj;  // преобразуем контейнерный объект в указатель на таблицу методов контейнера
	return (table->get)(obj, index, rv);              // вызываем метод "get" из таблицы методов контейнера и возвращаем результат
}
