#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void primes(int input_fd){
    int start;
    if(read(input_fd, &start, 4) != 4){
        exit(-1);
    }
    printf("prime %d\n", start);
    int fds[2];
    pipe(fds);
    int pid = fork();
    if(pid == 0){
        close(fds[1]);
        primes(fds[0]);
        close(fds[0]);
    }else{
        close(fds[0]);
        int num;
        while(read(input_fd, &num, 4) == 4){
            if(num % start != 0){
                write(fds[1], &num, 4);
            }
        }
        close(fds[1]);
    }
    wait(0);
    exit(0);
 
}

int main(int argc, char* argv[]){
    int fds[2];
    pipe(fds);
    int pid = fork();
    if(pid == 0){
        close(fds[1]);
        primes(fds[0]);
        close(fds[0]);
    }else{
        close(fds[0]);
        for(int i = 2; i <= 35; i++){
            write(fds[1], &i, 4);
        }
        close(fds[1]);

    }
    wait(0);
    exit(0);
}