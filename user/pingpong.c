#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char* argv[]){
    int fd[2];
    char buf[256];
    if(pipe(fd) == -1){
        exit(0);
    }

    int pid = fork();
    if(pid == 0){
        // child process
        read(fd[1], buf, 4);
        write(fd[0], "pong", 4);
        printf("%d: received ping\n", getpid());
        
    }else{
        // parent process
        write(fd[0], "ping", 4);
        // sleep(1);
        wait(0);
        read(fd[1], buf, 4);
        printf("%d: received pong\n", getpid());
    }
    exit(0);

}