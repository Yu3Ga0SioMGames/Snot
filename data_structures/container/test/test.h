#ifndef TEST_H_INCLUDED      // проверяем, чтобы содержимое файла не было включено более одного раза


#define TEST_H_INCLUDED      // определяем макрос, предотвращающего повторное включение содержимого файла


#include "../container.h"    // подключаем заголовочный файл "container.h"

//#include "../array.h"      // подключаем заголовочный файл "array.h"

#include "../../list/list.h" // подключаем заголовочный файл "list.h"


/// Функция для тестирования контейнерных объектов:
int main_container();


#endif                       // завершаем условное включение файла
