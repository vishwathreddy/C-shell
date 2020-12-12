#include <stdio.h>
#include <main.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void CtrlC_catch()
{
  if(curf_pid!=-1)
    kill(curf_pid,SIGKILL);    
  printf("CtrlC signal catched\n");
}
int main(int argc, char *argv[])
{
  signal(SIGINT,CtrlC_catch);
  main_loop();
  return 0;
}
