#include <main.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <stdlib.h>

int f_setenv(char ** arg)
{
    int no_arg=0, i;
	for(i=0; arg[i]!=NULL; i++)
	{
		no_arg = no_arg + 1;
		//printf("%s\n",arg[i]);
	}
	//printf("%d",no_arg);
    if(no_arg >=4)	
        printf("setenv: Too many arguments\nExpected two or three arguments \n");
	else if(no_arg <= 1)
		printf("setenv: Too few arguments\nExpected two or three arguments\n");
	else if(no_arg == 3)
		if(setenv(arg[1], arg[2], 1) == -1)
			perror("Error ocuured while running setenv");
	return 1;
}

int f_unsetenv(char **arg)
{
    int no_arg=0, i;
	for ( i = 0; arg[i] != NULL; ++i)
		no_arg = no_arg + 1;

	if(no_arg == 2)
		if(unsetenv(arg[1]) == -1)
			perror("Error ocuured while running unsetenv");
    else if(no_arg >= 3)	
        printf("setenv: Too many arguments\nExpected two arguments \n");
	else if(no_arg <= 1)
			printf("setenv: Too few arguments\nExpected two arguments\n");
	return 1;
}

int f_jobs(char **arg)
{
    /*jobq* cur = Head->next;
    int i=0;
    while(cur!=NULL)
    {
        i++;
        if(cur->state == 1)
            printf("[%d] \t Running \t %s \t [%d]\n",i, cur->name, cur->pid);
        else
            printf("[%d] \t Stopped \t %s \t [%d]\n",i, cur->name, cur->pid);
        cur = cur->next;
    }*/
	

	return 1;
}

int f_kjobs(char **arg)
{
    return 1;
}

int f_fg(char **arg)
{
    return 1;
}
int f_bg(char **arg)
{
    return 1;
}
int f_overkill(char **arg)
{
	return 1;
}

int f_quit()
{
	return 0;
}