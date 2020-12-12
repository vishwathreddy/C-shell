#include <main.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
int bgcount;
void handler(int sig)
{
  pid_t pid;
  pid = wait(NULL);
  if(pid!=-1)
    printf("\n%d done.\n", pid);
  bgcount--;
}
int f_launch(char ** arg)
{
    int pid, wpid;
    int status;
    signal(SIGCHLD, handler);
    int bgflag=0,i=0;
    int ispiped=0;
    while(arg[i]!=NULL)
        i++;
    i--;
    int l=strlen(arg[i]);  
    if(arg[i][l-1]=='&')
    {
      bgflag=1;
      arg[i] = NULL;
    }
    pid = fork();
    if (pid == 0)
    {   
        arg = redirect(arg);
        if(execvp(arg[0],arg)==-1)
        {
            perror("Cannot execute the command");
            exit(1);
        }
    } 
    else if (pid < 0)
    {
      perror("Error occured while creating process");
      exit(1);
    }
    else
    {
        curf_pid = pid;
        //parent process
        if (bgflag==0)
        {
            waitpid(pid, &status, WUNTRACED);
        }
        else
        {
            bgcount++;
            /*no_jobs++;
            Array[no_jobs] = (jobq *) malloc(sizeof(jobq));
            (Array[no_jobs])->pid = pid;
            strcpy((Array[no_jobs])->name, args[0]);
            */
            printf("[%d] %d\n", bgcount, pid);
            waitpid(pid, &status, WNOHANG);
        }
    }
    return 1;
}