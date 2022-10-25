#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

void cat(char* names[],int cnt,int E_flag,int n_flag)
{
    int flag=0;
    struct stat stats;
    char* copy=(char*)malloc(50);

    int file_des;
    FILE* file; 
    for(int i=0;i<cnt;i++)
    {
        flag=0;
        file=fopen(names[i],"r");
        if(!file)
        {
            printf("cat: %s: No such file or directory \n", names[i]);
            flag=1;
        }
        
        strcpy(copy,names[i]);
        stat(copy,&stats);
        
        if (S_ISDIR(stats.st_mode))
        {
            printf("cat: %s : is a directory\n",names[i]);
            flag=1;
        }

        char line[100];
        int cnt=0;

        if (flag==0)
        {
            while (fgets(line, sizeof(line), file)) 
            {
                cnt++;
                if (E_flag==0 && n_flag==0) printf("%s", line); 
                else if (E_flag==1) printf("$ %s", line);
                else if (n_flag==1) printf("%d %s",cnt, line);
            
            }
        }
        fclose(file);
        //printf("\n");
    }
}

void cat_from_terminal()
{
    while(1)
    {
        char input[50];
        scanf("%[^\n]%*c",input);
        if (strcmp(input,"break")==0) break;
        else 
        {
            printf("%s",input);
            printf("\n");
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
    //printf("%s\n",input);

    char * itr;
    char* input_clone1=(char*)malloc(50);
    char* input_clone2=(char*)malloc(50);
    char* input_clone3=(char*)malloc(50);
    strcpy(input_clone1,input);
    strcpy(input_clone2,input);
    strcpy(input_clone3,input);
    
    int cnt=0;
    char * str=(char*)malloc(50);
   
    char *token=strtok(input," "); //spliting
    strcpy(str,token);
    while( token != NULL ) 
    {
        token = strtok(NULL, " "); 
        cnt++; 
    }

    if (strcmp(str,"cat")==0 && cnt==1) // cat from terminal
    {

        //printf("command not supported\n");
        cat_from_terminal();
        return 0;
      

    }

    token=strtok(input_clone1," "); //first word again
    token = strtok(NULL, " ");  //second word again

    if(strcmp(token,"-E")==0)
    {
        token=strtok(input_clone2," "); //first word again
        token=strtok(NULL," "); 
        char* names[10]; //ten files to be read at max
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
        if (flag==0) cat(names,cnt-2,1,0);
        if (cnt==2 && flag!=1)
        {
             printf("command not supported\n");
        }

    }

    
    else if(strcmp(token,"-n")==0)
    {
        token=strtok(input_clone2," "); //first word again
        token=strtok(NULL," ");
        char* names[10]; //ten files to be read at max
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
        if (flag==0) cat(names,cnt-2,0,1);
        if (cnt==2 && flag!=1)
        {
            printf("command not supported\n");
        }
        

    }

    else if(token !=NULL) //normal cat
    {
        token=strtok(input_clone3," "); //first word again
        char* names[10]; //ten files to be read at max
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
        if (flag==0) cat(names,cnt-1,0,0);
    }
    else 
    {
        printf("command not found\n");
    }    
}
