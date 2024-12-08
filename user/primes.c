#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void get_prime(int p1[2]){
    close(p1[1]);

    //get a prime and print it
    int n;
    if(!read(p1[0],&n,4)){
        close(p1[0]);
        printf("pipe no data\n");
        exit(0);
    }
    printf("prime %d\n",n);

    //create pipe and fork a process, 
    //write all  primes in fprocess
    //read all data from pipe and print one prime(first data) in cprocess
    int p2[2];
    pipe(p2);
    int pid = fork();
    if(pid == 0){
        get_prime(p2);
    }
    else if(pid > 0){
        //printf("pid: %d\n",pid);
        int m;
        while(read(p1[0],&m,4)){
            if(m % n){
                write(p2[1],&m,4);
            }
        }
        close(p1[0]);
        close(p2[1]);
        close(p2[0]);
        wait(0);
    }
    else{
        printf("fork error\n");
        exit(pid);
    }
    exit(0);
}

int main(int argc,char * argv[]){

    int p[2];
    pipe(p);
    int i;
    for(i=2;i <= 35;i++){
        write(p[1],&i,4);
    }
    get_prime(p);
    exit(0);
}

