#ifndef COMMON_H_INCLUDED


// начало


#define COMMON_H_INCLUDED


/*
    Включает стандартную библиотеку "threads.h",
    которая предоставляет функции для работы с потоками
    (Например, создание и управление потоками):
*/
#include <threads.h>


#define BAD_ALLOC_ERROR 1                               // ошибка недостаточного выделения памяти
#define CONTAINER_NOT_PROVIDED (BAD_ALLOC_ERROR + 1)    // ошибка отсутствия контейнера
#define CONTAINER_IS_EMPTY (CONTAINER_NOT_PROVIDED + 1) // ошибка пустого контейнера

#define STACK_DATA_TYPE void *                          // определение типа данных для стека как указателя на void


extern thread_local int container_error;                // объявление локальной переменной потока для хранения ошибки контейнера


#endif                                                  // конец
