#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

void sortname(char A[256][256], int k) 
{
    char temp[1000];
    for(int i=0; i<k; i++) 
    {
        for(int j=0; j<(k-1-i); j++) 
        {
            if(strcmp(A[j], A[j+1]) > 0) 
            {
                strcpy(temp, A[j]);
                strcpy(A[j], A[j+1]);
                strcpy(A[j+1], temp);
            }
        }
    }

    for(int i=0;i<k;i++)
        printf("%s\n",A[i]);
}


void printdir(char *dir)
{
    char list[256][256];
    DIR *dp;
    int k=0;
    struct dirent *entry;
    struct stat fs;
    if ((dp=opendir(dir))==NULL)
    {
        fprintf(stderr,"cannot open directory: %s\n",dir);
        return;
    }

    chdir(dir);
    while((entry=readdir(dp))!=NULL)
    {
        lstat(entry->d_name , &fs);
        if(S_ISDIR(fs.st_mode))
        {
            if(strcmp(".",entry->d_name)==0 || strcmp("..",entry->d_name)==0)
                continue;
            strcpy(list[k],entry->d_name);
            k++;
        }

    }
    chdir("..");
    closedir(dp);
    sortname(list,k);
}

void main(int argc, char* args[])
{
    printdir(args[1]);
}
