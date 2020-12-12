#include <main.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Max_buffersize 100
char ** Get_args(char * input, char * sep)
{
    int size = Max_buffersize;
    char ** tokens = malloc(size * sizeof(char *));
    char * token;
    int pt = 0;
    if(!tokens)
    {
      printf("allocation error");
      exit(EXIT_FAILURE);
    }
    token = strtok(input,sep);
    while(token != NULL)
    {
      tokens[pt] = token;
      pt+=1;

      if(pt > size)
      {
        size += Max_buffersize;
        tokens = realloc(tokens,size * sizeof(char *));
        if(!tokens)
        {
          printf("allocation error" );
          exit(EXIT_FAILURE);
        }
      }
      token = strtok(NULL,sep);
    }
    tokens[pt] = NULL;
    return tokens;
}
