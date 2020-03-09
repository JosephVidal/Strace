/*
** EPITECH PROJECT, 2018
** my
** File description:
** my
*/

#pragma once

#include <stdbool.h>
#include <unistd.h>
#include <inttypes.h>

extern const int SUCCESS;
extern const int FAILURE;

typedef struct string_s
{
    char        *str;
    void        (*assign_s)(struct string_s *, const struct string_s *);
    void        (*assign_c)(struct string_s *, const char *);
    void        (*append_s)(struct string_s *, const struct string_s *);
    void        (*append_c)(struct string_s *, const char *);
    char        (*at)(const struct string_s *, size_t);
    void        (*clear)(struct string_s *);
    uint8_t     (*size)(const struct string_s *);
    uint8_t     (*compare_s)(const struct string_s *, const struct string_s *);
    uint8_t     (*compare_c)(const struct string_s *, const char *);
}   string_t;

#ifdef STR_METHOD_ONLY
void        assign_s(string_t *, const string_t *);
void        assign_c(string_t *, const char *);
void        append_s(string_t *, const string_t *);
void        append_c(string_t *, const char *);
char        at(const string_t *, size_t);
void        clear(string_t *);
uint8_t     size(const string_t *);
uint8_t     compare_s(const string_t *, const string_t *);
uint8_t     compare_c(const string_t *, const char *);
size_t      copy(const string_t *, char *, size_t, size_t);
#endif

void        my_free_tab(char **);
void        my_print_tab(char *const *);
uint8_t     my_printf(char const *, ...);
void        my_putchar(const char);
void        my_puterr(const char *);
uint8_t     my_putstr(const char *);
char        **my_strtwa(const char *, const char);
char        *my_strcat(char *, const char *);
bool        my_strcmp(char const *, char const *);
char        *my_strcpy(char *, char const *);
char        *my_strdup(const char *);
uint8_t     my_strlen(const char *);
uint8_t     my_tablen(char *const *);
