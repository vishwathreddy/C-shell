#include <main.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>

int piping(char **arg)
{
  int p[2],q[2];  
  int i=0,j=0,k=0,m=0,count=0;
  int end=0;
  int fd1, fd2, fd3;
  char *cpy[100];
  pid_t pid;
  int flag1=0;
  int flag2=0;
  int flag3=0;
  i=0;
  while(arg[m]!=NULL)
  {
    if(strncmp(arg[m],"|",1)==0)
        count++;
    m++;
  }
  count++;
  int last=count -1;
while(arg[j]!=NULL &&  end!=1)
{
    k = 0;
    char * d = arg[j];
    while((strncmp(d,"|",1)!=0))
    {
        cpy[k]=d;
        j++;
        d = arg[j];
        if(d == NULL)
        {
            end = 1;
            k++;
            break;
            flag1 = 1;
        }
        k++;
    }
    cpy[k] = NULL;
    j++;
    flag2 =1;
    if(i%2 != 0)
        pipe(p);
    else
        pipe(q);

    pid = fork();

    if (pid == 0)
    {
        char ** symm;
        symm = redirect(cpy);

        if (i==0)
            dup2(q[1],1);
        else if (i==last)
        {
            if(count%2!=0)
                dup2(p[0],0);
            else
                dup2(q[0],0);
        }

        else
        {   
            if(i%2==0)
            {
                flag2=1;
                dup2(q[0],0);
                dup2(p[1],1);
            }
            else
            {
                flag1=1;
                dup2(p[0],0);
                dup2(q[1],1);
            }
        }
        flag1=1;
        if(execvp(symm[0],symm)==-1)
        {   
            //kill(getpid(),SIGTERM);
            perror("Cannot execute the command");
            flag3=1;
        }
    }
    else
    {
        if(i==0)
            close(q[1]);
        else if(i==last)
        {
            if(i%2!=0)
                close(p[0]);
            else
                close(q[0]);
        }
        else
        {
            if(i%2==0)
            {
              close(p[0]);
              close(q[1]);
            }
            else
            {
              close(q[0]);
              close(p[1]);
            }
        }
        flag3=1;
        waitpid(pid,NULL,0);
        i++;
    }
}
    return 1;
}