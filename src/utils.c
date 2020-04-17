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

void usage(void)
{
    puts("USAGE: ./strace [-s] [-p <pid>|<command>]");
}
