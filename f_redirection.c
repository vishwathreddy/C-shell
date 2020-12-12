#include <main.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
char ** redirect(char **arg)
{
  int fd1,fd2,fd3;int j=0;
  int r=0,s=0,t=0;
  char input[200], out1[200], out2[200];
  /*while(arg[j]!=NULL)
  {   
    if(strncmp(arg[j],"<",1)==0)
    {
      arg[j]=NULL;
      r=1;
      strcpy(input,arg[j+1]);
      break;
    }
    j++;
  }
  j=0;
  while(arg[j]!=NULL)
  {
    if(strncmp(arg[j],">",1)==0)
    {
      arg[j]=NULL;
      s=1;
      strcpy(out1,arg[j+1]);
      break;
    }
    j++;
  }
  j=0;
  while(arg[j]!=NULL)
  {
    if(strcmp(arg[j],">>")==0)
    {
      arg[j]=NULL;
      t=1;
      strcpy(out2,arg[j+1]);
      break;
    }
    j++;
  }*/
  int k[3];
  int i=0;
  for(i=0;i<3;i++)
    k[i]=100;
  i=0;
  while(arg[j]!=NULL)
  {
    if(strncmp(arg[j],">",1)==0)
    {
      k[0]=j;
      s=1;
      strcpy(out1,arg[j+1]);
    }
    if(strncmp(arg[j],"<",1)==0)
    {
      k[1]=j;
      r=1;
      strcpy(input,arg[j+1]);
    }
    if(strcmp(arg[j],">>")==0)
    {
      k[2]=j;
      arg[j]=NULL;
      t=1;
      strcpy(out2,arg[j+1]);
    }
    j++;
  }
  int min =k[0];
  for(i=0;i<3;i++)
    if(k[i]<min)
      min=k[i];
  arg[min]=NULL;        
  if(r==0 && s==0 && t==0)
  {
      return arg;
  }
  if(r==1)
  {
    fd1 = open(input, O_RDONLY,0);
    if(fd1 < 0)
    {
      perror("Error occured while opening the input file");
      exit(0);
    }
    dup2(fd1,0);
    close(fd1);
  }
  if(s==1)
  {
      fd2 = open(out1, O_WRONLY | O_CREAT, 0644);
      if(fd2<0)
      {
        perror("Could not open the output file");
        exit(0);
      }
    dup2(fd2,1);
    close(fd2);
  }
  if(t==1)
  {
      fd3 = open(out2, O_WRONLY | O_CREAT | O_APPEND , 0644);
      if(fd3<0)
      {
        perror("Could not open the output file");
        exit(0);
      }
    dup2(fd3,1);
    close(fd3);
  }
  return arg;
}
