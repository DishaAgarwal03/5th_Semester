#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(int argc, char* args[])
{
    char dir[100];
    DIR *dp;
    struct dirent *entry;
    struct stat fs;

    strcpy(dir,args[1]);
    if ((dp=opendir(dir))==NULL)
    {
        fprintf(stderr,"cannot open directory: %s\n",dir);
        return 1;
    }

    chdir(dir);
    while((entry=readdir(dp))!=NULL)
    {
        if(strcmp(".",entry->d_name)==0 || strcmp("..",entry->d_name)==0)
                continue;
        printf("%s\t",entry->d_name);
        //file permissions:
        if(stat(entry->d_name, &fs) < 0)    
            return 1;
        printf( (S_ISDIR(fs.st_mode)) ? "d" : "-");
        printf( (fs.st_mode & S_IRUSR) ? "r" : "-");
        printf( (fs.st_mode & S_IWUSR) ? "w" : "-");
        printf( (fs.st_mode & S_IXUSR) ? "x" : "-");
        printf( (fs.st_mode & S_IRGRP) ? "r" : "-");
        printf( (fs.st_mode & S_IWGRP) ? "w" : "-");
        printf( (fs.st_mode & S_IXGRP) ? "x" : "-");
        printf( (fs.st_mode & S_IROTH) ? "r" : "-");
        printf( (fs.st_mode & S_IWOTH) ? "w" : "-");
        printf( (fs.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n\n");
    }
    chdir("..");
    closedir(dp);
}