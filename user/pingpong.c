#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MSGSIZE 5
char* msg1 = "ping";
char* msg2 = "pong";

int
main(){
    char buf[MSGSIZE];
    int fds[2];
    pipe(fds);

    int pid = fork();

    // parents process
    if(pid > 0){
        write(fds[1], msg1, MSGSIZE);		// 向fd[1]中写入	
        wait(0);							// 最好加上wait
        read(fds[0], buf, MSGSIZE);			// 从fd[0]中读出	
        printf("%d",getpid());
        printf(": received ");
        printf("%s\n",buf);
    }else{
        read(fds[0], buf, MSGSIZE);
        write(fds[1], msg2, MSGSIZE);
        printf("%d",getpid());
        printf(": received ");
        printf("%s\n",buf);
    }

    exit(0);
}