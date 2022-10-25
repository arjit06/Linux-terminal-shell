#include<stdio.h>
#include<time.h>
#include <string.h>
#include <stdlib.h>
void date()
{
    struct tm *time_info;
    time_t t;
    time(&t);
    char time_str[100];
    time_info = localtime(&t);

    strftime(time_str, 100, "%a %b %d %H:%M:%S %Z %Y\n", time_info);
    printf("%s\n", time_str);
}

void date_minus_u()
{
    struct tm *time_info;
    time_t t;
    time(&t);
    char time_str[100];
    time_info = gmtime(&t);


    strftime(time_str, 100, "%a %b %d %H:%M:%S UTC %Y\n", time_info);
    printf("%s\n", time_str);
}

void date_minus_R()
{
    struct tm *time_info;
    time_t t;
    time(&t);
    char time_str[100];
    time_info = localtime(&t);

    strftime(time_str, 100, "%a, %b %d %Y %H:%M:%S %z\n", time_info);
    printf("%s\n", time_str);
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
    char  *itr,*token;
    char* input_clone1=(char*)malloc(50);
    strcpy(input_clone1,input);
    token=strtok(input," ");
 
    if (strcmp(token,"date")==0)
    {
        token = strtok(NULL, " ");  //second word
        if (token==NULL) //date
        {
            date();
        }
        else 
        {
            token=strtok(input_clone1," "); //first word
            token = strtok(NULL, " ");  //second word
            if (strcmp(token,"-u")==0)
            {
                token = strtok(NULL, " "); //third word
                if (token!=NULL) 
                {
                    printf("command not found\n");
                }
                else  // date -u
                {
                    date_minus_u();
                }
            }
            else if (strcmp(token,"-R")==0)
            {
                token = strtok(NULL, " "); //third word
                if (token!=NULL) 
                {
                    printf("command not found\n");
                }
                else  // date -R
                {
                    date_minus_R();
                }
            }
            else 
            {
                printf("command not found\n");
            }
        }
    }
    else
    {
        printf("command not found\n");
        
    }
}