#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

void remove_all_files(char* names[],int cnt,int flag)
{
    int retval;
    for(int i=0;i<cnt;i++)
    {
        //printf("%s ",names[i]);
        if (strcmp(names[i],"makefile")==0|| strcmp(names[i],"maincode.c")==0 || strcmp(names[i],"ls.c")==0 || strcmp(names[i],"mkdir.c")==0 || strcmp(names[i],"rm.c")==0 || strcmp(names[i],"date.c")==0 || strcmp(names[i],"cat.c")==0|| strcmp(names[i],"maincode")==0 || strcmp(names[i],"ls")==0 || strcmp(names[i],"rm")==0 || strcmp(names[i],"mkdir")==0 || strcmp(names[i],"date")==0)
        {
            printf("ERROR: can't delete project files\n");
        }
        else 
        {
            retval=remove(names[i]);
            if (flag==1 && retval==0)
            {
                printf("rm: file removed %s\n",names[i]);
            }
            if (retval !=0)
            {
                printf("rm: cannot remove %s: either does not exist or Directory not empty\n",names[i]); //file doesn't exist or file an unempty directory

            }
        }
    }


}

void rm(char* names[],int cnt,int flag)
{
    struct stat stats;
    char* copy=(char*)malloc(50);

    int retval;
    for(int i=0;i<cnt;i++)
    {
        // printf("%s ",names[i]);
        if (strcmp(names[i],"makefile")==0|| strcmp(names[i],"maincode.c")==0 || strcmp(names[i],"ls.c") ==0|| strcmp(names[i],"mkdir.c")==0 || strcmp(names[i],"rm.c")==0 || strcmp(names[i],"date.c")==0 || strcmp(names[i],"cat.c")==0|| strcmp(names[i],"maincode")==0|| strcmp(names[i],"ls")==0 || strcmp(names[i],"rm")==0 || strcmp(names[i],"mkdir")==0 || strcmp(names[i],"date")==0)
        {
            printf("ERROR: can't delete project files\n");
        }
        else 
        { 
            strcpy(copy,names[i]);
            stat(copy,&stats);
            
            if (S_ISDIR(stats.st_mode))
            {
                printf("rm: cannot remove %s: is a directory\n",names[i]);
            }
            else
            {
                retval=remove(names[i]);
                if (flag==1 && retval==0)
                {
                    printf("rm: file removed %s\n",names[i]);
                }
                if (retval !=0)
                {
                    printf("rm: cannot remove %s: No such file or directory\n",names[i]);
                }
            }
        }
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
    char * itr;
    char* input_clone1=(char*)malloc(50);
    char* input_clone2=(char*)malloc(50);
    char* input_clone3=(char*)malloc(50);
    strcpy(input_clone1,input);
    strcpy(input_clone2,input);
    strcpy(input_clone3,input);

    int cnt=0;
    char *token=strtok(input," "); //spliting
    while( token != NULL ) 
    {
        token = strtok(NULL, " "); 
        cnt++; 
    }

    token=strtok(input_clone1," "); //spliting
    token = strtok(NULL, " "); //second word

    if (strcmp(token,"-d")==0)
    {
        char* names[10]; //ten files to be deleted at max
        int idx=0,flag=0;

        itr=strtok(input_clone2," "); //first
        itr= strtok(NULL, " "); //second
    
        while(itr != NULL ) 
        {
            itr= strtok(NULL, " "); //third
            if (itr!=NULL)
            {
                if (itr[0]=='-')
                {
                    printf("rm: invalid option: %s\n",itr);
                    flag=1;
                    break;
                } 
                names[idx++]=itr;
            }
        }
        if (flag==0) remove_all_files(names,cnt-2,0);


    }
    else if (strcmp(token,"-v")==0)
    {
        char* names[10]; //ten files to be deleted at max
        int idx=0,flag=0;

        itr=strtok(input_clone2," "); //first
        itr= strtok(NULL, " "); //second
    
        while(itr != NULL ) 
        {
            itr= strtok(NULL, " "); //third
            if (itr!=NULL)
            {
                if (itr[0]=='-')
                {
                    printf("rm: invalid option: %s\n",itr);
                    flag=1;
                    break;
                } 
                names[idx++]=itr;
            }
        }
        if (flag==0) rm(names,cnt-2,1);

    }
    else 
    {
        char* names[10]; //ten files to be deleted at max
        int idx=0,flag=0;

        itr=strtok(input_clone2," "); //first
    
        while(itr != NULL ) 
        {
            itr= strtok(NULL, " "); //second
            if (itr!=NULL)
            {
                if (itr[0]=='-')
                {
                    printf("rm: invalid option: %s\n",itr);
                    flag=1;
                    break;
                } 
                names[idx++]=itr;
                //printf("%s\n",names[idx-1]);
            }
        }
        if (flag==0) rm(names,cnt-1,0);
    }
}