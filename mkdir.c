#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
//implement mkdir -p while do cd 
void make_directories(char* names[],int cnt,int flag)
{

    int retval;
    for(int i=0;i<cnt;i++)
    {
        // printf("%s ",names[i]);
        retval=mkdir(names[i],0755);
        if (flag==1 && retval==0)
        {
            printf("mkdir: created directory %s\n",names[i]);
        }
        if (retval !=0)
        {
            printf("Unable to create directory %s\n",names[i]);

        }
    }

}

void mkdir_p(char* names[],int cnt)
{
    struct stat stats; 
    int retval;                                         
    char* token;
    char *clone=(char*)malloc(50),*clone_2=(char*)malloc(50); 
    char name[50]="";                                                                                                                                                                        

    for(int i=0;i<cnt;i++)
    {
        strcpy(clone,names[i]);
        token=strtok(clone,"/");
        strcpy(name,"");
        strcpy(clone_2,"");
        
        while(token!=NULL)
        {
            strcpy(name,clone_2);
            
            strcat(name,token);
            strcpy(clone_2,name);
            strcat(name,"/");
            
            //printf("%s ",name);
            stat(name,&stats);
            strcat(clone_2,"/"); 
            int ans=S_ISDIR(stats.st_mode);
            if (!ans) //not a directory already
            {
                //printf("%s ",clone_2);
                retval=mkdir(name,0755);
                if (retval !=0)
                {
                    printf("Unable to create directory %s\n",name);

                }
            }
            //else printf("%s ",clone_2);
            token=strtok(NULL,"/");
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
    // printf("%s~\n",input);
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

    if (strcmp(input_clone1,"mkdir")==0)
    {
        printf("mkdir: missing operand\n");
        return 0;
    }

    token=strtok(input_clone1," "); //first word again
    token = strtok(NULL, " ");  //second word again

    if(strcmp(token,"-v")==0)
    {
        token=strtok(input_clone2," "); //first word again
        token=strtok(NULL," "); 
        char* names[10]; //ten directories to be created at max
        int idx=0,flag=0;
    
        while( token != NULL ) 
        {
            token = strtok(NULL, " ");
            if (token!=NULL)
            {
                if (token[0]=='-')
                {
                    printf("command not found\n");
                    flag=1;
                    break;
                } 
            names[idx++]=token;
            }
        }
        if (flag==0) make_directories(names,cnt-2,1);
        if (cnt==2)
        {
            printf("mkdir: missing operand");
        }

    }
    else if(strcmp(token,"-p")==0)
    {
        token=strtok(input_clone2," "); //first word again
        token=strtok(NULL," ");
        char* names[10]; //ten directories to be created at max
        int idx=0,flag=0;
    
        while( token != NULL ) 
        {
            token = strtok(NULL, " ");
            if (token!=NULL)
            {
                if (token[0]=='-')
                {
                    printf("command not found\n");
                    flag=1;
                    break;
                } 
                names[idx++]=token;
                //printf("%s ",names[idx-1]);
            }
        }
        if (flag==0) mkdir_p(names,cnt-2);
        if (cnt==2)
        {
            printf("mkdir: missing operand");
        }
        

    }

    else if(token !=NULL) //normal mkdir
    {
        token=strtok(input_clone3," "); //first word again
        char* names[10]; //ten directories to be created at max
        int idx=0,flag=0;
    
        while( token != NULL ) 
        {
            token = strtok(NULL, " ");

            if ( token !=NULL)
            {
                if (token[0]=='-')
                {
                    printf("command not found\n");
                    flag=1;
                    break;
                } 
                names[idx++]=token;
            }
        }
        if (flag==0) make_directories(names,cnt-1,0);
    }
    else 
    {
        printf("command not found\n");
    }    
}