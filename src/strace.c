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

bool check_call(pid_t pid)
{
    siginfo_t sig = {0};

    ptrace(PTRACE_GETSIGINFO, pid, NULL, &sig);
    return (sig.si_code & 0x80 || sig.si_code & 0x80cd || sig.si_code & 0x050f);
}

pid_t check_args(int argc, char *const *args, uint8_t *mode)
{
    pid_t tmp = 0;

    if (argc == 3 && (!strcmp(args[1], "-p") && atoi(args[2]))) {
        tmp = atoi(args[2]);
        *mode = STRACE_ATTACH;
    } else {
        tmp = fork();
        *mode = STRACE_EXEC;
    }
    if (tmp == -1)
        perror("fork");
    return(tmp);
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

void trace_child(pid_t pid, struct user_regs_struct regs
                    , int32_t *sig, uint8_t mode)
{
    errno = 0;
    waitpid(pid, sig, 0);
    if (mode == STRACE_ATTACH)
        ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    else
        ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD);
    while (WIFSTOPPED(*sig) || WIFEXITED(*sig)) {
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        if (check_call(pid))
            display_call(regs);
        if (ptrace(PTRACE_SINGLESTEP, pid, 0, 0) != 0 && errno) {
		    perror("ptrace");
            return;
        }
        waitpid(pid, sig, 0);
    }
    if (mode == 1)
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
}

uint8_t strace(const char *file, char *const *args,
                char * const *env, int argc)
{
    int32_t sig = 0;
    uint8_t mode = 0;
    struct user_regs_struct regs = {0};
    pid_t pid = check_args(argc, args, &mode);

    if (pid == -1)
        return (FAILURE);
    if (pid == 0) {
        ptrace(PT_TRACE_ME, 0, 0, 0);
        if (execve(file, &args[1], env) == -1) {
            perror(file);
            return (FAILURE);
        }
    } else {
        trace_child(pid, regs, &sig, mode);
        printf("+++ exited with %d +++\n", WEXITSTATUS(sig));
    }
    return (WEXITSTATUS(sig));
}
