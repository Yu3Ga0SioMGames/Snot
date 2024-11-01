#ifndef ACCBS_H_INCLUDED
#define ACCBS_H_INCLUDED


#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <string.h>

#include <threads.h>


#define FILE_SIZE 512

#define PUNCTUATION ",;."
#define WHITESPACE " \t\n"
#define OPENING_BRACKETS "({[<"
#define CLOSING_BRACKETS ")}]>"
#define BRACKETS OPENING_BRACKETS CLOSING_BRACKETS


extern thread_local int64_t error;


void str_free_str(char *);

void str_accbs(const char *);

void str_print_str(const char *);

void str_free_tokens(char **, size_t);

void str_get_file_path(char *, size_t);

void str_print_tokens(char **, size_t);


bool str_is_matching_pair(char, char);


char str_is_delimiter(char);

char *str_read_file(const char *);

char **str_split_str(const char *, size_t *);


#endif
