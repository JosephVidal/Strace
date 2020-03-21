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
    char **args = NULL;
    uint8_t ret = 0;

    if (argc < 2 || !env) {
        usage();
        return (FAILURE);
    }
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        usage();
        return (SUCCESS);
    }
    args = get_args(argc, argv);
    if (args == NULL)
        return (FAILURE);
    ret = strace(argv[1], args, env);
    free_tab(args);
    return (ret);
}
