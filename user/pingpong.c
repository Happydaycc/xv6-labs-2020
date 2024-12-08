#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){

    int p1[2],p2[2];
    pipe(p1);
    pipe(p2);
    int pid = fork();

    if(pid > 0){//parent process
        close(p1[0]);
        close(p2[1]);
        char rbuf[1] = {0};
        write(p1[1],"p",1);

        if(read(p2[0],rbuf,1) == 1)
        {
            printf("%d: received pong\n",getpid());
            close(p1[1]);
            close(p2[0]);
            exit(0);
        }
    }else if(pid == 0){//child process
        close(p1[1]);
        close(p2[0]);
        char rbuf[1] = {0};
        if(read(p1[0],rbuf,1) == 1){    //if read succeed
            printf("%d: received ping\n",getpid());
            write(p2[1],"p",1);
        }
        
        close(p1[0]);
        close(p2[1]);
    }
    exit(0);
}