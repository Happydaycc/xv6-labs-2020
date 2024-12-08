#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc < 2){//if no argument
        //write(1,"No additional arguments provided.");
        fprintf(2, "No additional arguments provided.\n");
        exit(1);
    }
    else if(argc > 2){//if too much arguments
        fprintf(2, "Arguments exceed .\n");
        exit(1);
    }
    else{
        int tag = 1;
        char *p = argv[1];
        while(*p){
            if(*p < '0' || *p > '9'){ //if not number
                tag = 0;    //set the flag eql 0
                break;
            }
            p++;
        }
        if(tag == 1){   //if no problem
            sleep(atoi(argv[1]));
        }
        else{   //error
            fprintf(2, "Arguments errors.\n");
            exit(1);
        }
    }
    exit(0);
}