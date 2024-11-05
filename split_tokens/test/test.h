/*
    Этот директив препроцессора проверяет, не определен ли макрос "TEST_H_INCLUDED".
    Если макрос не определен, код внутри условного блока будет обработан:
*/
#ifndef TEST_H_INCLUDED

/*
    Определяет макрос "TEST_H_INCLUDED".
    Это предотвращает многократное включение этого заголовочного файла в один и тот же файл.
    Благодаря этому директиву, следующий раз при включении "TEST_H_INCLUDED"
    компилятор пропустит содержимое между "#ifndef" и "#endif":
*/
#define TEST_H_INCLUDED

/// Подключаем заголовочный файл, в котором содержатся общие определения и функции для теста:
#include "../split_tokens.h"

void test_split_tokens(); // объявление функции "void test_split_tokens()"

/*
    Закрывает условный блок препроцессора, начатый директивой "#ifndef".
    Если макрос "TEST_H_INCLUDED" не был определен до этого,
    код между "#ifndef" и "#endif" будет включен:
*/
#endif

/// Смысл этого заголовочного файла в использовании тестовых функций.
