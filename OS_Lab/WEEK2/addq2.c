#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

int main()
{
    DIR *dp;
    struct dirent *entry;
    struct stat fs;
    int ch;
    char cwd[256];

    getcwd(cwd, sizeof(cwd));
    if ((dp=opendir(cwd))==NULL)
    {
        fprintf(stderr,"cannot open directory: %s\n",dir);
        return 1;
    }
    while((entry=readdir(dp))!=NULL)
    {
        lstat(entry->d_name , &fs);
        if(S_ISDIR(fs.st_mode))
        {
            continue;
        }
        printf("Delete %s?(1/0):  ",entry->d_name);
        scanf("%d",&ch);
        if(ch==1)
        {
            if (remove(entry->d_name) == 0)
                printf("Deleted successfully\n");
            else
                printf("Unable to delete the file\n");
        }
    }
    chdir("..");
    closedir(dp);
}