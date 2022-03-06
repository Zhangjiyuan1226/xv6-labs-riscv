#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#define MSGSIZE 16
int
main(int argc, char *argv[])	// 这个arg参数存在一些问题，去掉const可以编译
{
    sleep(10);
    /*
    管道会将前面指令的标准输出重定向到标准输入，
    所以只需从fd = 0的标准输入中读出指令即可
    */
    char buf[MSGSIZE]; 
    read(0, buf, MSGSIZE);

    // exec 命令和附加参数
    char *xargv[MAXARG];       // 指令的参数
    int xargc = 0;
    int times = 1;
    if(strcmp(argv[1], "-n") != 0){
        for(int i = 1; i < argc; i++){
            xargv[xargc++] = argv[i];
        }
    }else{
        times = atoi(argv[2]);
        for(int i = 3; i < argc; i++){
            xargv[xargc++] = argv[i];
        }
    }
    char *p = buf;

    for(int i = 0; i < MSGSIZE; i++){
        if(buf[i] == '\n'){
            int pid = fork();
            if(pid > 0){
                p = &buf[i + 1];
                wait(0);
            }else{
                buf[i] = 0;
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0;
                xargc++;
                for(int j = 0; j < times;j++)
                    exec(xargv[0], xargv);
                exit(0);
            }
        }
    }

    exit(0);
    return 0;
}
