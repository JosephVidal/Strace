/*
** EPITECH PROJECT, 2020
** Strace
** File description:
** utils
*/

#include "strace.h"

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>

void free_tab(char **tab)
{
    for (register uint8_t i = 0; tab[i] != NULL; i++)
        if (tab[i])
            free(tab[i]);
    if (tab)
        free(tab);
}

void usage(void)
{
    puts("USAGE: ./strace [-s] [-p <pid>|<command>]");
}
