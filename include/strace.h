/*
** EPITECH PROJECT, 2019
** Strace
** File description:
** strace
*/

#pragma once

#define _POSIX_C_SOURCE 200809L

#include <inttypes.h>

#if defined (__linux__)
    #include <elf.h>
#endif // __linux__

#define SUCCESS 0
#define FAILURE 84

uint8_t strace(const char *, char *const *, char *const *);
void free_tab(char **);
char **get_args(uint32_t, const char **);
void usage(void);
