/*
** EPITECH PROJECT, 2019
** Strace
** File description:
** strace
*/

#pragma once

#define _POSIX_C_SOURCE 200809L

#include <stdint.h>

#define SUCCESS 0
#define FAILURE 84

#if defined (__APPLE__)
    #define	PTRACE_GETREGS          (PT_FIRSTMACH + 1)
    #define PTRACE_GETSIGINFO	    0x4202
    #define PTRACE_SETOPTIONS	    0x4200
    #define PTRACE_O_TRACESYSGOOD	1
    #define PTRACE_SINGLESTEP	    9


    typedef uint32_t u_int;
    typedef uint8_t u_char;
    typedef uint16_t u_short;

    struct user_regs_struct {
        __extension__ uint64_t r15;
        __extension__ uint64_t r14;
        __extension__ uint64_t r13;
        __extension__ uint64_t r12;
        __extension__ uint64_t rbp;
        __extension__ uint64_t rbx;
        __extension__ uint64_t r11;
        __extension__ uint64_t r10;
        __extension__ uint64_t r9;
        __extension__ uint64_t r8;
        __extension__ uint64_t rax;
        __extension__ uint64_t rcx;
        __extension__ uint64_t rdx;
        __extension__ uint64_t rsi;
        __extension__ uint64_t rdi;
        __extension__ uint64_t orig_rax;
        __extension__ uint64_t rip;
        __extension__ uint64_t cs;
        __extension__ uint64_t eflags;
        __extension__ uint64_t rsp;
        __extension__ uint64_t ss;
        __extension__ uint64_t fs_base;
        __extension__ uint64_t gs_base;
        __extension__ uint64_t ds;
        __extension__ uint64_t es;
        __extension__ uint64_t fs;
        __extension__ uint64_t gs;
	};
#endif // __APPLE__

uint8_t strace(const char *, char *const *, char *const *);
void    free_tab(char **);
char    **get_args(uint32_t, const char **);
void    usage(void);
