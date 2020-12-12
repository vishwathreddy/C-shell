void main_loop();
char * get_input();
char ** Get_args(char * input, char * sep);
int f_Execute(char ** arg);
int f_cd(char ** arg);
int f_pwd();
int f_echo(char ** arg);
int f_ls(char ** arg);
int f_simplels(char ** arg);
int f_lsa(char **arg);
int f_lsal(char **arg);
int f_pinfo(char **arg);
int f_notbin(char **arg);
int f_launch(char **arg);
int f_setenv(char **arg);
int f_unsetenv(char **arg);
int f_jobs(char **arg);
int f_kjobs(char **arg);
int f_fg(char **arg);
int f_bg(char **arg);
int f_overkill(char **arg);
int f_quit();
char ** redirect(char **arg);
int piping(char **arg);
void CtrlC_catch();
int curf_pid;
char Home[200];
int no_jobs;
struct node
{
	char name[1000];
	int pid;
	int state;
};
typedef struct node jobq;
jobq Array[200];


