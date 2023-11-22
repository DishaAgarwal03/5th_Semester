//inode of the softlink is diff from the original link

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char *args[])
{
    char new[]="/home/OS_Student/Desktop/OS_210905412/WEEK4/q4";
    int ret;
    if(argc<2)
    {
        fprintf(stderr,"usage: %s <file>\n",args[0]);
        return 1;
    }
    ret=symlink(args[1],new);
    if (ret)
    {
        perror("Symlink creation");
        return 1;
    }
    printf("Created soft link!\n");
    printf("Link Path: %s\n",new);
    ret=remove(new);
    if (ret)
    {
        perror("Symlink removal");
        return 1;
    }
    printf("Removed soft link!\n");
    
}
