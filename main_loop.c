#include <main.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void main_loop()
{
  char *input;
  char **args;
  char **arg;
  int flag=1;
  int i=0,j;
  getcwd(Home,200);
  do
  {
    char *username = getenv("USER");
    char path[200];
    char dispath[200];
    char hostname[500];
    char upath[500];
    gethostname(hostname,500);
    getcwd(path, 200);
    if(strcmp(Home,path)==0)
    {
        dispath[0]='~';
        dispath[1]='\0';
    }
    else
    {
      int flag2=0;
      j=0;
      int l = strlen(path);
      for(i=0;i<strlen(Home);i++)
      {
        if(path[i]!= Home[i])
        {
          flag2=1;
          break;
        }
      }
      if(flag2==1)
      {
        strcpy(dispath,path);
        dispath[i]='\0';
      }
      else
      {
        upath[0] = '~';
        for(j=1;i<l;j++,i++)
          upath[j] = path[i];
        upath[j] = '\0';
        strcpy(dispath,upath);
      }
    }
    printf("%s@%s>> %s >> ",username,hostname,dispath);
    input = get_input();
    args = Get_args(input,";");
    for(i=0;args[i]!=NULL;i++)
    {
      arg = Get_args(args[i], " \t\r\n\a");
      flag = f_Execute(arg);
      free(arg);
    }
  free(input);
  }while(flag);
}
