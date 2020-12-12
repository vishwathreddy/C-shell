#include <main.h>
#include <unistd.h>
#include <stdio.h>

char *get_input()
{
  char *var = NULL;
  ssize_t size = 0;
  getline(&var,&size, stdin);
  return var;
}
