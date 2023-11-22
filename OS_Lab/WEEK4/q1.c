#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char *args[])
{
    struct stat sb;
    int ret;
    if(argc<2)
    {
        fprintf(stderr,"usage: %s <file>\n",args[0]);
        return 1;
    }
    ret=stat(args[1],&sb);
    if (ret)
    {
        perror("Stat");
        return 1;
    }
    printf("Inode number of %s is %ld\n",args[1],sb.st_ino);
}
