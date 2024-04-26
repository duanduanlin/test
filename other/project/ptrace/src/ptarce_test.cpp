/*
 * @Author: dding3 dding3@jmc.com.cn
 * @Date: 2024-04-25 19:53:14
 * @LastEditors: dding3 dding3@jmc.com.cn
 * @LastEditTime: 2024-04-25 19:58:23
 * @FilePath: /test/test/other/project/ptrace/src/process_test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/reg.h>

int main(void)
{
    pid_t child;
    long orig_rax;
    child = fork();
    if (child == 0)
    {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("/bin/ls", "ls", "-l", "-h", NULL);
    }
    else
    {
        wait(NULL);
        orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
        printf("Child process called a system call, id is %ld\n", orig_rax);
        ptrace(PTRACE_CONT, child, NULL, NULL);
    }

    return 0;
}