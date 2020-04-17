/*
** EPITECH PROJECT, 2019
** Strace
** File description:
** main
*/

#include "strace.h"

#include <unistd.h>
#include <string.h>

int main(int argc, const char **argv, char *const *env)
{
    if (argc < 2 || !env) {
        usage();
        return (FAILURE);
    }
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        usage();
        return (SUCCESS);
    }
    return (strace(argv[1], (char *const *)argv, env, argc));
}
