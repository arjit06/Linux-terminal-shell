#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
void* mythread(void* arg)
{
    char** ARGS=(char**)arg;
    char* input=(char*)malloc(100);
    strcpy(input,ARGS[1]);
    
    if (strcmp(ARGS[2],"ls")==0)
    {
        //write the aboslute path of your executable file of ls here
        char arg[100]="/mnt/c/Users/ARJIT/OneDrive/Desktop/IIITD/SEM_3/OS/ASS1/shell/./ls ";
        strcat(arg,input);
       //printf("%s~\n",arg);
        system(arg);

    }
    else if (strcmp(ARGS[2],"cat")==0)
    {
        //write the aboslute path of your executable file of cat here
        char arg[100]="/mnt/c/Users/ARJIT/OneDrive/Desktop/IIITD/SEM_3/OS/ASS1/shell/./cat ";
        strcat(arg,input);
        //printf("%s~\n",arg);
        system(arg);

    }
    else if (strcmp(ARGS[2],"mkdir")==0)
    {
        //write the aboslute path of your executable file of mkdir here
        char arg[100]="/mnt/c/Users/ARJIT/OneDrive/Desktop/IIITD/SEM_3/OS/ASS1/shell/./mkdir ";
        strcat(arg,input);
        //printf("%s~\n",arg);
        system(arg);

    }
    else if (strcmp(ARGS[2],"date")==0)
    {
        //write the aboslute path of your executable file of date here
        char arg[100]="/mnt/c/Users/ARJIT/OneDrive/Desktop/IIITD/SEM_3/OS/ASS1/shell/./date ";
        strcat(arg,input);
        // printf("%s~\n",arg);
        system(arg);

    }
    else if (strcmp(ARGS[2],"rm")==0)
    {
        //write the aboslute path of your executable file of rm here
        char arg[100]="/mnt/c/Users/ARJIT/OneDrive/Desktop/IIITD/SEM_3/OS/ASS1/shell/./rm ";
        strcat(arg,input);
        // printf("%s~\n",arg);
        system(arg);
    }
}

void echo_minus_help()
{
    char str[]="Usage: echo [SHORT-OPTION]... [STRING]...\n\
  or:  echo LONG-OPTION\n\
Echo the STRING(s) to standard output.\n\
\n\
  -n             do not output the trailing newline\n\
  --help         display this help and exit\n\
\n\
NOTE: your shell may have its own version of echo, which usually supersedes\n\
the version described here.  Please refer to your shell's documentation\n\
for details about the options it supports.\n\
\n\
GNU coreutils online help: <https://www.gnu.org/software/coreutils/>\n\
Report echo translation bugs to <https://translationproject.org/team/>\n\
Full documentation at: <https://www.gnu.org/software/coreutils/echo>\n\
or available locally via: info '(coreutils) echo invocation'\n";
    printf("%s",str);
}

void handle_echo(char* input)
{
    char* clone=(char*)malloc(50);
    strcpy(clone,input);
    //printf("%s",clone);
    char* token=strtok(input," ");
    if(strcmp(token,"echo")==0)
    {
        token=strtok(NULL," "); //second word
        
        if (token==NULL)
        {
            printf("\n");
            return;
        }
    }
    
    if (strcmp(token,"-n")==0)
    {
        token = strtok(NULL, " "); //third word
        if (token!=NULL) 
        {
            while (token!=NULL)
            {
                printf("%s",token);
                token=strtok(NULL," ");  
                if(token !=NULL) printf(" ");          
            }
            
        }

    }
    else if(strcmp(token,"--help")==0)
    {
        char str[50]="";
        char* itr;
        token = strtok(NULL, " "); //third word
        if (token!=NULL) 
        {
            itr=strtok(clone," ");
            while (itr!=NULL)
            {
                //printf("%s\n",itr);
                itr=strtok(NULL," ");
                if (itr!=NULL)
                {
                    strcat(str,itr);
                    strcat(str," ");
                }  
            }
            printf("%s\n",str);
        }
        else  // echo --help
        {
            echo_minus_help();

        }
    }
    else //normal echo
    {
        while (token!=NULL)
        {
            printf("%s ",token);
            token=strtok(NULL," ");            
        }
        printf("\n");
    }
}

void Cwd()
{
    char cwd[PATH_MAX];  //PATH_MAX is system(chr) limit for path of a file (similar to INT_MAX) 
    getcwd(cwd,sizeof(cwd));
    printf("%s\n",cwd);
}


void handle_pwd(char* input)
{
    char* clone=(char*)malloc(50);
    strcpy(clone,input);
    char* token=strtok(input," ");

    if(strcmp(token,"pwd")==0)
    {
        token=strtok(NULL," "); //second word
        
        if (token==NULL) //normal pwd 
        {
            Cwd();
        }
        else if(strcmp(token,"-L")==0)
        {
            token=strtok(NULL," "); //third word
            if (token==NULL)
            {
                Cwd();
            }
            else 
            {
                printf("command not found\n");
            }

        }
        else if(strcmp(token,"-P")==0)
        {
            printf("invalid option\n");

        }
        else 
        {
            printf("command not found\n");
        }
    }

}

void cd(char* dname,char * prevDir)
{
    char name[50]="";
    strcat(name,dname);

    int retval;
    char cwd[PATH_MAX];  //PATH_MAX is system(chr) limit for path of a file (similar to INT_MAX) 
    getcwd(cwd,sizeof(cwd));
    
    retval=chdir(name);
    if (retval!=0)
    {
        printf("ERROR: No such directory\n");
    }
    else 
    {
        strcpy(prevDir,cwd);
    }
}

void change_to_home_dir(char* prevDir)
{
    char *homedir = getenv("HOME");
    cd(homedir,prevDir);
}

void handle_cd(char* input,char* prevDir)
{ 
    char* clone=(char*)malloc(50);
    strcpy(clone,input);
    char* token=strtok(input," ");
    char * itr;
    char *str=(char*)malloc(50);

    token =strtok(NULL," "); //second
    
    if (token !=NULL) //default cd 
    {
        itr=strtok(clone," "); //first
        itr=strtok(NULL," "); //second
        strcpy(str,itr);
        itr=strtok(NULL," "); //third
        //printf("%s\n",str);
        if (itr!=NULL)
        {
            while(itr!=NULL)
            {
                strcat(str,itr);
                itr=strtok(NULL," ");
            }
            printf("-bash: cd: too many arguments\n");
        }
        else 
        {
            if (strcmp(str,"~")==0) //home directory 
            {
                change_to_home_dir(prevDir);
            }
            else if (strcmp(str,"-")==0) // go to previous working directory
            {
                if (strcmp(prevDir,"")==0)
                {
                    printf("-bash: cd: OLDPWD not set\n");
                }
                else 
                {
                    printf("%s\n",prevDir);
                    cd(prevDir,prevDir);
                }

            }
            else 
            {
                cd(str,prevDir);
            }

        }
    }
    else  //cd to home
    {
        change_to_home_dir(prevDir);
    }
}

int main()
{
    pthread_t t;
    int flag=0;
    // // Creating a new thread
    // pthread_create(&ptid, NULL, &func, NULL);

  
    
    char * prevDir=(char*)malloc(50);
    char *str=(char*)malloc(100);
    char *args[3]; //array of strings (arguments)
   
    pid_t p;
    int status,space=1;

    while (1)  
    {
        flag=0;
        if (space==1)
        {
            printf("\n");
            space=0;
        }
        char hostname[HOST_NAME_MAX];
        gethostname(hostname, HOST_NAME_MAX);
        strcpy(str,hostname);
        strcat(str,":");

        char cwd[PATH_MAX];  //PATH_MAX is system(chr) limit for path of a file (similar to INT_MAX) 
        getcwd(cwd,sizeof(cwd));
        strcat(str,cwd);
        printf("%s$ ",str);  

        //path of binary of ls
        char path_ls_bin[]="/mnt/c/Users/ARJIT/OneDrive/Desktop/IIITD/SEM_3/OS/ASS1/shell/ls"; //write the aboslute path of your executable file of ls here
        char path_mkdir_bin[]="/mnt/c/Users/ARJIT/OneDrive/Desktop/IIITD/SEM_3/OS/ASS1/shell/mkdir"; //write the aboslute path of your executable file of mkdir here
        char path_date_bin[]="/mnt/c/Users/ARJIT/OneDrive/Desktop/IIITD/SEM_3/OS/ASS1/shell/date"; //write the aboslute path of your executable file of date here
        char path_rm_bin[]="/mnt/c/Users/ARJIT/OneDrive/Desktop/IIITD/SEM_3/OS/ASS1/shell/rm"; //write the aboslute path of your executable file of rm here
        char path_cat_bin[]="/mnt/c/Users/ARJIT/OneDrive/Desktop/IIITD/SEM_3/OS/ASS1/shell/cat"; //write the aboslute path of your executable file of cat here

        char input[50],t_input[50]="";
        char input_clone[50];
        char input_clone2[50];
        char input_clone3[50];
        char input_clone4[50];
        scanf("%[^\n]%*c",input);
        strcpy(input_clone,input);
        strcpy(input_clone2,input);
        strcpy(input_clone3,input);
        strcpy(input_clone4,input);

        //printf("%s~1\n",input);


        char* token=strtok(input_clone2," ");
        int cnt=0;
        while (token!=NULL)
        {
            cnt++;
            token=strtok(NULL," ");
        }
        //printf("%d\n",cnt);

        int idx=0;
        token=strtok(input_clone3," ");
        while (idx!=cnt-1)
        {
            idx++;
            token=strtok(NULL, " ");
        }
        //printf("%s\n",token);
        
        if (strcmp(token,"&t")==0)
        {
            idx=0;
            char* itr=strtok(input_clone4," ");
            while (idx !=cnt-1)
            {
                strcat(t_input,itr);
                if (idx!=cnt-2) strcat(t_input," ");
                idx++;
                itr=strtok(NULL," ");
            }
            flag=1;//threads
            strcpy(input,t_input);
        }

      // printf("%d\n",flag);
        


        
        token=strtok(input_clone," "); //spliting on space

        if (strcmp(token,"ls")==0) //ls implementation (first word is ls)
        { 
            args[1]=(char*)malloc(50);
            strcpy(args[1],input); //args 1 is input string
            args[2]=NULL;

            if (flag==0)
            {
                p=fork();
                if (p==0) //child process 
                {
                    args[0]=path_ls_bin; //complete path of executable file of ls.c
                    //execl(args[0],args);
                    execl(args[0],args[0],args[1],NULL);
                    exit(0);
                    
                }
                else if (p>0)  //parent process
                {
                    wait(&status);
                }   
                else 
                {
                    printf("fork error\n");
                }  
            }
            if (flag==1) 
            {
                args[2]=(char*)malloc(50);
                strcpy(args[2],"ls");
                // Creating a new thread
                pthread_create(&t, NULL, &mythread, args);
                pthread_join(t, NULL);
                //pthread_exit(NULL);

            }  
        }

        else if (strcmp(token,"mkdir")==0) //mkdir implementation (first word is mkdir)
        {
            args[0]=path_mkdir_bin; //complete path of executable file of mkdir.c
            args[1]=(char*)malloc(50);
            strcpy(args[1],input); //args 1 is input string
            args[2]=NULL;

            if (flag==0)
            {
                p=fork();
                if (p==0) //child process 
                {
                    execl(args[0],args[0],args[1],NULL);
                    exit(0);
                }
                else if (p>0)  //parent process
                {
                    wait(&status);
                }   
                else 
                {
                    printf("fork error\n");
                } 
            }  
            if (flag==1) 
            {
                args[2]=(char*)malloc(50);
                strcpy(args[2],"mkdir");
                // Creating a new thread
                pthread_create(&t, NULL, &mythread, args);
                pthread_join(t, NULL);
                //pthread_exit(NULL);

            }  
        }

        else if (strcmp(token,"date")==0) //date implementation
        {
            args[0]=path_date_bin; //complete path of executable file of date.c
            args[1]=(char*)malloc(50);
            strcpy(args[1],input); //args 1 is input string
            args[2]=NULL;
 
            if (flag==0)
            {
                p=fork();
                if (p==0) //child process 
                {
                    execl(args[0],args[0],args[1],NULL);
                    exit(0);
                }
                else if (p>0)  //parent process
                {
                    wait(&status);
                }   
                else 
                {
                    printf("fork error\n");
                }  
            } 
            if (flag==1) 
            {
                args[2]=(char*)malloc(50);
                strcpy(args[2],"date");
                // Creating a new thread
                pthread_create(&t, NULL, &mythread, args);
                pthread_join(t, NULL);
                //pthread_exit(NULL);

            }  
        }

        else if (strcmp(token,"rm")==0)
        {
            args[0]=path_rm_bin; //complete path of executable file of date.c
            args[1]=(char*)malloc(50);
            strcpy(args[1],input); //args 1 is input string
            args[2]=NULL;

            if (flag==0)
            {
                p=fork();
                if (p==0) //child process 
                {
                    execl(args[0],args[0],args[1],NULL);
                    exit(0);
                }
                else if (p>0)  //parent process
                {
                    wait(&status);
                }   
                else 
                {
                    printf("fork error\n");
                }   
            }
            if (flag==1) 
            {
                args[2]=(char*)malloc(50);
                strcpy(args[2],"rm");
                // Creating a new thread
                pthread_create(&t, NULL, &mythread, args);
                pthread_join(t, NULL);
                //pthread_exit(NULL);

            }  
            
        }

        else if (strcmp(token,"cat")==0)
        {
            args[0]=path_cat_bin; //complete path of executable file of date.c
            args[1]=(char*)malloc(50);
            strcpy(args[1],input); //args 1 is input string
            args[2]=NULL;

            if (flag==0)
            {
                p=fork();
                if (p==0) //child process 
                {
                    execl(args[0],args[0],args[1],NULL);
                    exit(0);
                }
                else if (p>0)  //parent process
                {
                    wait(&status);
                }   
                else 
                {
                    printf("fork error\n");
                }  
            } 
            if (flag==1) 
            {
                args[2]=(char*)malloc(50);
                strcpy(args[2],"cat");
                // Creating a new thread
                pthread_create(&t, NULL, &mythread, args);
                pthread_join(t, NULL);
                //pthread_exit(NULL);

            }  
            
        }
        

        else if (strcmp(token,"echo")==0)
        {
            handle_echo(input);
        }

        else if (strcmp(token,"pwd")==0)
        {
            handle_pwd(input);
        }

        else if (strcmp(token,"cd")==0)
        {
            handle_cd(input,prevDir);
        }

        else if (strcmp(token,"exit")==0)
        {
            break;

        }
        else 
        {
            printf("command not found\n");
        }
   }  
}
