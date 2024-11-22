#ifndef READER_H_INCLUDED

/// Начало:

#define READER_H_INCLUDED

#include "scaner/split_tokens/test/test.h" // подключаем заголовочный файл для тестирования разбивки токенов
#include "scaner/console_io/console_io.h"  // подключаем заголовочный файл для работы с консольным вводом-выводом
#include "parser/test/test.h"              // подключаем заголовочный файл для тестирования парсера
#include "parser/parser.h"                 // подключаем заголовочный файл с реализацией парсера

Expression *reader(Expression *);  // один из этапов создания Своего Языка Программирования

#endif                                     // конец
