#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

/*
    find <path> <filename>
    查找指定目录下是否有指定文件
    举例：find ./ a

*/

void find(char * path,char * fname){
    char buf[512],*p;
    int fd;
    struct stat st;
    struct dirent de;

    //打开目录，获取句柄
    if((fd = open(path, 0)) < 0){
        fprintf(2, "cannot open %s\n",path);
        return;
    }
    /*
    copy from ls.c
    read the path, find all file and dir,
    combine path and filename,then stat it
    if file, compare the filename with filename searched
    if dir ,open it and search recursively by "find()"
    */
    strcpy(buf, path);
    p = buf+strlen(buf);//指向buf最后一位的下一位
    *p++ = '/';
    //读取path路径目录下的文件
    //遍历目录中的目录项，存入目录项结构体de中
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        //printf("%s ", de.name);
        if(de.inum == 0)
            continue;
        //将文件名拼接到路径后面
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        //获取文件信息
        if(stat(buf, &st) < 0){
            printf("find: cannot stat %s\n", buf);
            continue;
        }
        //判断是文件还是目录
        //如果是文件，比较文件名，如果是目录，递归查找，直到找到文件，或者遍历完所有目录
        if(st.type == T_FILE){
            //如果是普通文件，比较文件名与fname,如果相同，打印路径
            //printf("this is a file\n");
            if(!strcmp(fname,de.name)){
                printf("%s\n",buf);
            }
        }else if (st.type == T_DIR)
        {
            //printf("this is a dir\n");
            //排除目录 . ..
            if(strcmp(de.name,".")  && strcmp(de.name,"..")){
                find(buf,fname);
            }
        }
    }
    close(fd);
    return;
}

/*
    查找指定目录下是否有指定文件
    find <path> <filename>
    举例：find . a

*/
int main(int argc,char * argv[]){

    if(argc < 2){
        printf("find error! no filename");
        exit(0);
    }
    //printf("%s  %s",argv[1],argv[2]);
    find(argv[1],argv[2]);
    exit(0);
}
