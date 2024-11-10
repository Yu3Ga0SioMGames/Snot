#ifndef COMMON_H_INCLUDED


#define COMMON_H_INCLUDED


/*
    Включает стандартную библиотеку "threads.h",
    которая предоставляет функции для работы с потоками
    (Например, создание и управление потоками):
*/
#include <threads.h>


#define BAD_ALLOC_ERROR 1
#define CONTAINER_NOT_PROVIDED (BAD_ALLOC_ERROR + 1)
#define CONTAINER_IS_EMPTY (CONTAINER_NOT_PROVIDED + 1)

#define STACK_DATA_TYPE void *


extern thread_local int container_error;


#endif
