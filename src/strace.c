/*
** EPITECH PROJECT, 2019
** Strace
** File description:
** strace
*/

#include "strace.h"
#include "syscalls.h"

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <errno.h>

char **get_args(uint32_t argc, const char **argv)
{
    char **buff = malloc(sizeof(char *) * argc);
    register uint8_t i = 1;

    if (!buff) {
        perror("get_args");
        return (NULL);
    }
    for (; argv[i] != NULL || i < argc; i++) {
        buff[i - 1] = strdup(argv[i]);
        if (!buff[i - 1]) {
            perror("get_args");
            return (NULL);
        }
    }
    buff[i - 1] = NULL;
    return (buff);
}

bool check_call(pid_t pid)
{
    siginfo_t sig = {0};

    ptrace(PTRACE_GETSIGINFO, pid, NULL, &sig);
    if (sig.si_code & 0x80 || sig.si_code & 0x80cd || sig.si_code & 0x050f)
        return (true);
    return (false);
}

void display_call(struct user_regs_struct regs)
{
    if ((signed)regs.orig_rax == -1)
        return;
    printf("%s(", g_syscalls[regs.orig_rax].name);
    if (g_syscalls[regs.orig_rax].param1 != 0)
        printf("0x%llx", regs.rdi);
    if (g_syscalls[regs.orig_rax].param2 != 0)
        printf(", 0x%llx", regs.rsi);
    if (g_syscalls[regs.orig_rax].param3 != 0)
        printf(", 0x%llx", regs.rdx);
    if (g_syscalls[regs.orig_rax].param4 != 0)
        printf(", 0x%llx", regs.rcx);
    if (g_syscalls[regs.orig_rax].param5 != 0)
        printf(", 0x%llx", regs.r8);
    if (g_syscalls[regs.orig_rax].param6 != 0)
        printf(", 0x%llx", regs.r9);
    printf(") = 0x%llx\n", regs.rax);
}

void trace_child(pid_t pid, struct user_regs_struct regs, int32_t sig)
{
    errno = 0;
    waitpid(pid, &sig, 0);
    ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD);
    while (WIFSTOPPED(sig)) {
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        if (check_call(pid))
            display_call(regs);
        if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) != 0 && errno) {
		    perror("ptrace");
            return;
        }
        waitpid(pid, &sig, 0);
    }
}

uint8_t strace(const char *file, char *const *args, char * const *env)
{
    int32_t sig = 0;
    pid_t pid = fork();
    int8_t ret = 0;
    struct user_regs_struct regs = {0};

    if (pid == -1) {
        perror("strace");
        return (FAILURE);
    }
    if (pid == 0) {
        ptrace(PT_TRACE_ME, 0, 0, 0);
        ret = execve(file, args, env);
        if (ret == -1)
            perror(file);
    } else
        trace_child(pid, regs, sig);
    printf("+++ exited with %d +++\n", ret);
    return (ret);
}
