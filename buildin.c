#include <main.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <stdlib.h>
int f_cd(char **arg)
{
  char a_path[200];
  char n_path[200];
  int n,j,k;
  n=strlen(Home);
  int i;
  if(arg[1]==NULL)
  {
    i=chdir(Home);
    if(i!=0)
      perror("Error occured while changing the directory");
    return 1;
  }
  if(arg[1][0]!='~')
  {
    getcwd(n_path,200);
    strcpy(a_path,n_path);
    //printf("%s\n",Home);
    int l = strlen(n_path);
    a_path[l]='/';
    j=l+1;
    for(k=0;k<strlen(arg[1]);k++,j++)
      a_path[j]=arg[1][k];
    a_path[j]='\0';
    //printf("%s\n",a_path);
    i=chdir(a_path);
    //printf("%d\n",i);
    if(i!=0)
      perror("Error occured while changing the directory");
    return 1;
  }
  else
  {
    strcpy(a_path,Home);
    j=n;
    for(k=1;k<strlen(arg[1]);k++,j++)
      a_path[j]=arg[1][k];
    a_path[j]='\0';
    i=chdir(a_path);
    if(i!=0)
      perror("Error occured while changing the directory");
    return 1;
  }
}
int f_pwd()
{
  char dispath[200];
  getcwd(dispath,200);
  printf("%s\n",dispath);
  return 1;
}
int f_echo(char ** arg)
{
  int i;
  for(i=1;arg[i]!=NULL;i++)
    printf("%s ",arg[i]);
  printf("\n");
  return 1;
}
int f_pinfo(char **arg)
{
  char pid[10];
  if(arg[1]==NULL)
    sprintf(pid, "%d", getpid());
  else
    strcpy(pid, arg[1]);
  char dir[]="/proc/";
  char con[4000];
  char exePath[300];
  char symPath[50];
  char **stat;
  strcat(dir, pid);
  strcpy(symPath, dir);
  strcat(dir, "/stat");
  strcat(symPath, "/exe");
  int t = readlink(symPath, exePath, sizeof(exePath));
  if(t == -1)
    strcpy(exePath, "broken link");
  exePath[t] = '\0';
  char dispath[300];
  if(strcmp(Home,exePath)==0)
  {
      dispath[0]='~';
      dispath[1]='\0';
  }
  else
  {
    int flag=0;
    int j=0,i;
    int l = strlen(exePath);
    for(i=0;i<strlen(Home);i++)
    {
      if(exePath[i]!= Home[i])
      {
        flag=1;
        break;
      }
    }
    if(flag==1)
    {
      strcpy(dispath,exePath);
      dispath[i]='\0';
    }
    else
    {
      char upath[300];
      upath[0] = '~';
      for(j=1;i<l;j++,i++)
        upath[j] = exePath[i];
      upath[j] = '\0';
      strcpy(dispath,upath);
    }
    int fd = open(dir, O_RDONLY);
    if(fd == -1)
    {
      perror("Cannot open the directory\n");
      return 1;
    }
    read(fd, con, 250);
    stat = Get_args(con, " \t\r\n\a");
    printf("pid -- %s\nProcess Status -- %s\nVirtual Memory-- %s\nExecutable Path -- %s\n", stat[0], stat[2], stat[23], dispath);
    return 1;
  }
}
