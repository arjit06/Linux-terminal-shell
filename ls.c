#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
//review while doing cd
struct stat stats;
void ls(char* name, int flag) //print all files except hidden files
{
    
    DIR *d;
    struct dirent *dirPtr;
    char cwd[PATH_MAX];  //PATH_MAX is system(chr) limit for path of a file (similar to INT_MAX) 
    if (getcwd(cwd,sizeof(cwd))!=NULL) //opening CURRENT WORKING DIRECTORY
    {
        if (flag==1)
        {
            strcat(cwd,"/");
            strcat(cwd,name);
        }

        stat(name,&stats);
        int ans=S_ISDIR(stats.st_mode);

        if (!ans && flag==1)
        {
            printf("No such file or directory\n");
            return;
        }
        d=opendir(cwd); //open current directory and load the directory stream in d
        dirPtr=readdir(d); //traverse through directories
        while (dirPtr!=NULL)
        {
            if ((dirPtr->d_name)[0]!='.') //&& strcmp(dirPtr->d_name,"..")!=0) 
            {
                printf("%s  ",dirPtr->d_name);
            }
            dirPtr=readdir(d);
            
        }
        printf("\n");
    }

    else 
    {
        printf("getcwd() error\n");
    }
}

void ls_Minus_a(char* name,int flag) //include hidden files as well
{
    DIR *d;
    struct dirent *dirPtr;
    char cwd[PATH_MAX];  //PATH_MAX is system(chr) limit for path of a file (similar to INT_MAX) 
    if (getcwd(cwd,sizeof(cwd))!=NULL) //opening CURRENT WORKING DIRECTORY
    {
        if (flag==1)
        {
            strcat(cwd,"/");
            strcat(cwd,name);
        }
        stat(name,&stats);
        int ans=S_ISDIR(stats.st_mode);

        if (!ans && flag==1)
        {
            printf("No such file or directory\n");
            return;
        }
        d=opendir(cwd); //open current directory and load the directory stream in d
       
        dirPtr=readdir(d); //traverse through directories
        while (dirPtr!=NULL)
        {
            printf("%s  ",dirPtr->d_name);
            dirPtr=readdir(d);
        }
        printf("\n");
    }

    else 
    {
        printf("getcwd() error\n");
    }

}

void ls_Minus_1(char* name,int flag) //same as ls but print files in seperate lines
{
    DIR *d;
    struct dirent *dirPtr;
    char cwd[PATH_MAX];  //PATH_MAX is system(chr) limit for path of a file (similar to INT_MAX) 
    if (getcwd(cwd,sizeof(cwd))!=NULL) //opening CURRENT WORKING DIRECTORY
    {
        if (flag==1)
        {
            strcat(cwd,"/");
            strcat(cwd,name);
        }
        stat(name,&stats);
        int ans=S_ISDIR(stats.st_mode);

        if (!ans && flag==1)
        {
            printf("No such file or directory\n");
            return;
        }
        d=opendir(cwd); //open current directory and load the directory stream in d
        dirPtr=readdir(d); //traverse through directories
        while (dirPtr!=NULL)
        {
            if ((dirPtr->d_name)[0]!='.') //&& strcmp(dirPtr->d_name,"..")!=0) 
            {
                printf("%s\n",dirPtr->d_name);
            }
            dirPtr=readdir(d);
            
        }
        printf("\n");
    }

    else 
    {
        printf("getcwd() error\n");
    }

}

int main(int n, char* args[])
{
    char input[100]="";
    if (n==2)
    {
        strcpy(input,args[1]);
    }

    else 
    {
        for(int i=1;i<n;i++)
        {
            strcat(input,args[i]);
            if (i!=n-1) strcat(input," ");
        }

    }
    //printf("%s~\n",input);
    char * try;
    char *token=strtok(input," "); //spliting
    token = strtok(NULL, " "); //second word

    if (token ==NULL) //normal ls
    {
        ls("",0);
    }
    else 
    {
        if (strcmp(token,"-a")==0) 
        {
            token = strtok(NULL, " "); //third word
            if (token!=NULL) 
            {
                char* name=(char*)malloc(50);
                strcpy(name,token);
                token=strtok(NULL," "); //fourth word
                if (token!=NULL)
                {
                    printf("command not found\n");
                }
                else
                {
                    ls_Minus_a(name,1);
                }
            }
            else  // ls -a
            {
                ls_Minus_a("",0);
            }
        }
        else if (strcmp(token,"-1")==0)
        {
            token = strtok(NULL, " "); //third word
            if (token!=NULL) 
            {
                char* name=(char*)malloc(50);
                strcpy(name,token);
                token=strtok(NULL," "); //fourth word
                if (token!=NULL)
                {
                    printf("command not found\n");
                }
                else
                {
                    ls_Minus_1(name,1);
                }
            }
            else // ls -1
            {
                ls_Minus_1("",0);
            }
        }
        else 
        {
            char* name=(char*)malloc(50);
            strcpy(name,token);
            token=strtok(NULL," ");
            if (token!=NULL)
            {
                printf("command not found\n");
            }
            else
            {
                ls(name,1);
            }
           
        }
    }
}