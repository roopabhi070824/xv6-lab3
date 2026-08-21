#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
    printf("[parent] my pid is %d\n", getpid());
    printf("[parent] forking a child process\n");

    int pid = fork();

    if(pid < 0){
        printf("fork failed\n");
        exit(1);
    }

    if(pid == 0){
        printf("[child] my pid is %d\n", getpid());
        printf("[child] my parent is %d\n", getppid());
        exit(0);
    }

    wait(0);
    exit(0);
}
