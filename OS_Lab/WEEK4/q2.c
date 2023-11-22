#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
int main(int argc, char *args[])
{
    struct stat sb;
    time_t ct;
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

    ct=sb.st_ctime;
    // the time() function returns the number of seconds elapsed "since 00:00, Jan 1 1970 UTC"
    //time_t therefore gives number of seconds -> %ld
    //localtime(&(sb.st_atime)) does not work  ??
    //last status time does not change unless file is modified...why?
    //what is status change?
    printf("ID of device containing file: %ld \nInode number: %ld 
    \nPermissions: %d \nNumber of hard links: %ld \nUser ID of owner: %d 
    \nGroup ID of owner: %d \nDevice ID: %ld \nTotal size: %ld bytes 
    \nBlocksize for filesystem I/O: %ld \nNumber of blocks allocated: %ld 
    \nLast access time: %sLast Modification time: %sLast status change time: %s",
    sb.st_dev, sb.st_ino ,sb.st_mode, sb.st_nlink,sb.st_uid,sb.st_gid,sb.st_rdev,
    sb.st_size,sb.st_blksize,sb.st_blocks,ctime(&sb.st_atime),ctime(&sb.st_mtime),
    ctime(&ct));
}
