//inode of the hardlinks are the same

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char *args[])
{
    char new[]="/home/OS_Student/Desktop/OS_210905412/WEEK4/q3";
    struct stat sb;
    int ret,retstat;
    if(argc<2)
    {
        fprintf(stderr,"usage: %s <file>\n",args[0]);
        return 1;
    }
    retstat=stat(args[1],&sb);
    if (retstat)
    {
        perror("Stat\n");
        return 1;
    }
    printf("Number of hard links: %ld\n",sb.st_nlink);

    ret=link(args[1],new);
    if (ret)
    {
        perror("Link creation\n");
        return 1;
    }
    printf("Created hard link!\n");
    printf("Link Path: %s\n",new);
    retstat=stat(args[1],&sb);
    printf("Number of hard links: %ld\n",sb.st_nlink);
    //may print the number of hard links using stat 
    //to check if hard link created/destroyed
    
    ret=unlink(new);
    if (ret)
    {
        perror("Link removal\n");
        return 1;
    }
    printf("Removed hard link!\n");
    retstat=stat(args[1],&sb);
    printf("Number of hard links: %ld\n",sb.st_nlink);
}
