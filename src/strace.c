/*
** EPITECH PROJECT, 2019
** Strace
** File description:
** strace
*/

#include "strace.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **get_args(uint32_t argc, const char **argv)
{
    char **buff = malloc(sizeof(char *) * argc -1);
    register uint8_t i = 2;

    if (!buff) {
        perror("get_args");
        return (NULL);
    }
    for (; argv[i] != NULL || i < argc; i++) {
        buff[i - 2] = strdup(argv[i]);
        if (!buff[i - 2]) {
            perror("get_args");
            return (NULL);
        }
    }
    buff[i - 2] = NULL;
    return (buff);
}

uint8_t strace(const char *file, char *const *args, char *const *env)
{
    int32_t sig = 0;
    pid_t pid = fork();

    if (pid == -1) {
        perror("strace");
        return (FAILURE);
    }
    if (pid == 0)
        execve(file, args, env);
    else
        waitpid(pid, &sig, 0);
    return (SUCCESS);
}
