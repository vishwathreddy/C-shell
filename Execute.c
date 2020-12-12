#include <main.h>
#include <stdio.h>
#include <string.h>

int f_Execute(char ** arg)
{ 
  int i=0;
  int ispiped=0;
  while(arg[i]!=NULL)  
  {
    if(strcmp(arg[i],"|")==0)
      ispiped=1;
    i++;
  }
  if(arg[0]==NULL)
    return 1;
  else if(strcmp(arg[0],"setenv")==0)
    return f_setenv(arg);
  else if(strcmp(arg[0],"unsetenv")==0)
    return f_unsetenv(arg);
  else if(strcmp(arg[0],"jobs")==0)
    return f_jobs(arg);
  else if(strcmp(arg[0],"kjobs")==0)
    return f_kjobs(arg);
  else if(strcmp(arg[0],"fg")==0)
    return f_fg(arg);
  else if(strcmp(arg[0],"bg")==0)
    return f_bg(arg);
  else if(strcmp(arg[0],"overkill")==0)
    return f_overkill(arg);
  else if(strcmp(arg[0],"quit")==0)
    return f_quit();
  else
    {
      if(ispiped==0)
        return f_launch(arg);
      else
        return piping(arg); 
    } 
  return 1;
}
