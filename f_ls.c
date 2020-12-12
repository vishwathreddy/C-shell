#include <main.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pwd.h>

int f_lsa(char **arg)
{
    DIR * d;
    struct dirent *dirc;
    if(arg[2]==NULL)
    {
        char path[200];
        getcwd(path,200);
        d = opendir(path);
        if(d!=NULL)
        {
          while ((dirc = readdir(d))!=NULL)
              printf("%s\n",dirc->d_name);
          return 1;
        }
        else
        {
          printf("ls: cannot access : directory or file\n");
          return 1;
        }
    }
    else
    {
      int i=1,l,j,n,k;
      while(arg[i]!=NULL)
      {
        char a_path[200];
        getcwd(a_path,200);
        l = strlen(a_path);
        n = strlen(arg[i]);
        a_path[l]='/';
        for(j=l+1,k=0;k<n;j++,k++)
          a_path[j]=arg[i][k];
        a_path[j]='\0';
        struct stat file;
        if(arg[i][0]=='-')
        {
          i++;
          continue;
        }
        if(stat(a_path,&file) == 0 && S_ISREG(file.st_mode))
        {
          printf("%s\n",arg[i]);
          i++;
        }
        else
        {
          d = opendir(a_path);
          if(d!=NULL)
          {
            while ((dirc = readdir(d))!=NULL)
                printf("%s\n",dirc->d_name);
            i++;
          }
          else
          {
            printf("ls: cannot access : directory or file\n");
            return 1;
          }
        }
      }
    }
}

int f_lsal(char **arg)
{
    int i=1,flag=0;
    while(arg[i]!=NULL)
    {
      if(arg[i][0]=='-')
        if((strcmp(arg[i],"-a")==0)||(strcmp(arg[i],"-la")==0)||(strcmp(arg[i],"-al")==0))
          flag=1;
      i++;
    }
    if(flag==0)
    {
      if(arg[2]==NULL)
      {
        DIR *d;
        struct dirent *dirc;
        char path[200];
        getcwd(path,200);
        d = opendir(path);
        if(d==NULL)
        {
          printf("ls: cannot access : directory or file\n");
          return 1;
        }
        else
        {
          while((dirc = readdir(d))!=NULL)
          {
            if(dirc->d_name[0]!='.')
            {
              struct stat filestatus;
              struct passwd *p;
              struct group *g;
              char t_path[200];
              t_path[0]='\0';
              int l=strlen(path),i,j;
              strcpy(t_path,path);
              t_path[l]='/';
              int m=strlen(dirc->d_name);
              for (i=l+1,j=0;j<m;i++,j++)
                t_path[i]=dirc->d_name[j];
              t_path[i]='\0';
              if(stat(t_path,&filestatus)>=0)
              {
                printf( (S_ISDIR(filestatus.st_mode)) ? "d" : "-");
                printf( (filestatus.st_mode & S_IRUSR) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWUSR) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXUSR) ? "x" : "-");
                printf( (filestatus.st_mode & S_IRGRP) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWGRP) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXGRP) ? "x" : "-");
                printf( (filestatus.st_mode & S_IROTH) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWOTH) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXOTH) ? "x " : "- ");
                printf("%lu ",filestatus.st_nlink);
                p = getpwuid(filestatus.st_uid);
                g = getgrgid(filestatus.st_gid);
                printf("%s %s ",p->pw_name,g->gr_name);
                printf("%-6ld ",filestatus.st_size);
                char t[100];
                strcpy(t,ctime(&filestatus.st_mtime));
                t[16]=0;
                printf("%s ",t);
                printf("%s\n",dirc->d_name);
              }
              else
              {
                printf("Error cannot access the file or directory %s\n",dirc->d_name);
                return 1;
              }
            }
          }
          return 1;
        }
      }
      else
      {
          int i=1,l,j,n,k;
          while(arg[i]!=NULL)
          {
            char a_path[200];
            getcwd(a_path,200);
            l = strlen(a_path);
            n = strlen(arg[i]);
            a_path[l]='/';
            for(j=l+1,k=0;k<n;j++,k++)
              a_path[j]=arg[i][k];
            a_path[j]='\0';
            struct stat filestatus;
            struct group *g;
            struct passwd *p;
            if(arg[i][0]=='-')
            {
              i++;
              continue;
            }
            if(stat(a_path,&filestatus) == 0 && S_ISREG(filestatus.st_mode))
            {
              char file_name[200];
              for(j=strlen(a_path)-1;;i--)
                if(a_path[j]=='/')
                  break;
              for(k=j,l=0;l<strlen(a_path);k++,l++)
                file_name[k]=a_path[l];
              if(stat(a_path,&filestatus)>=0)
              {
                printf( (S_ISDIR(filestatus.st_mode)) ? "d" : "-");
                printf( (filestatus.st_mode & S_IRUSR) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWUSR) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXUSR) ? "x" : "-");
                printf( (filestatus.st_mode & S_IRGRP) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWGRP) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXGRP) ? "x" : "-");
                printf( (filestatus.st_mode & S_IROTH) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWOTH) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXOTH) ? "x " : "- ");
                printf("%lu ",filestatus.st_nlink);
                p = getpwuid(filestatus.st_uid);
                g = getgrgid(filestatus.st_gid);
                printf("%s %s ",p->pw_name,g->gr_name);
                printf("%-6ld ",filestatus.st_size);
                char t[100];
                strcpy(t,ctime(&filestatus.st_mtime));
                t[16]=0;
                printf("%s ",t);
                printf("%s\n",file_name);
              }
              else
              {
                printf("Error cannot access the file or directory %s\n",file_name);
                return 1;
              }
              i++;
              continue;
            }
            else
            {
              DIR *d;
              struct dirent *dirc;
              d=opendir(a_path);
              if(d==NULL)
              {
                printf("ls: cannot access : directory or file\n");
                return 1;
              }
              else
              {
                while((dirc = readdir(d))!=NULL)
                {
                  if(dirc->d_name[0]!='.')
                  {
                    struct stat filestatus;
                    struct passwd *p;
                    struct group *g;
                    char t_path[200];
                    t_path[0]='\0';
                    int l=strlen(a_path),i,j;
                    strcpy(t_path,a_path);
                    t_path[l]='/';
                    int m=strlen(dirc->d_name);
                    for (j=l+1,k=0;k<m;j++,k++)
                      t_path[j]=dirc->d_name[k];
                    t_path[j]='\0';
                    if(stat(t_path,&filestatus)>=0)
                    {
                      printf( (S_ISDIR(filestatus.st_mode)) ? "d" : "-");
                      printf( (filestatus.st_mode & S_IRUSR) ? "r" : "-");
                      printf( (filestatus.st_mode & S_IWUSR) ? "w" : "-");
                      printf( (filestatus.st_mode & S_IXUSR) ? "x" : "-");
                      printf( (filestatus.st_mode & S_IRGRP) ? "r" : "-");
                      printf( (filestatus.st_mode & S_IWGRP) ? "w" : "-");
                      printf( (filestatus.st_mode & S_IXGRP) ? "x" : "-");
                      printf( (filestatus.st_mode & S_IROTH) ? "r" : "-");
                      printf( (filestatus.st_mode & S_IWOTH) ? "w" : "-");
                      printf( (filestatus.st_mode & S_IXOTH) ? "x " : "- ");
                      printf("%lu ",filestatus.st_nlink);
                      p = getpwuid(filestatus.st_uid);
                      g = getgrgid(filestatus.st_gid);
                      printf("%s %s ",p->pw_name,g->gr_name);
                      printf("%-6ld ",filestatus.st_size);
                      char t[100];
                      strcpy(t,ctime(&filestatus.st_mtime));
                      t[16]=0;
                      printf("%s ",t);
                      printf("%s\n",dirc->d_name);
                    }
                    else
                    {
                      printf("Error cannot access the file or directory %s\n",dirc->d_name);
                      return 1;
                    }
                  }
                }
                i++;
                continue;
              }
            }
          }
          return 1;
      }
    }
    else
    {
        if(arg[2]==NULL || arg[3]==NULL)
        {
          DIR *d;
          struct dirent *dirc;
          char path[200];
          getcwd(path,200);
          d = opendir(path);
          if(d==NULL)
          {
            printf("ls: cannot access : directory or file\n");
            return 1;
          }
          else
          {
            while((dirc = readdir(d))!=NULL)
            {
              struct stat filestatus;
              struct passwd *p;
              struct group *g;
              char t_path[200];
              t_path[0]='\0';
              int l=strlen(path),i,j;
              strcpy(t_path,path);
              t_path[l]='/';
              int m=strlen(dirc->d_name);
              for (i=l+1,j=0;j<m;i++,j++)
                t_path[i]=dirc->d_name[j];
              t_path[i]='\0';
              if(stat(t_path,&filestatus)>=0)
              {
                printf( (S_ISDIR(filestatus.st_mode)) ? "d" : "-");
                printf( (filestatus.st_mode & S_IRUSR) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWUSR) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXUSR) ? "x" : "-");
                printf( (filestatus.st_mode & S_IRGRP) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWGRP) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXGRP) ? "x" : "-");
                printf( (filestatus.st_mode & S_IROTH) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWOTH) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXOTH) ? "x " : "- ");
                printf("%lu ",filestatus.st_nlink);
                p = getpwuid(filestatus.st_uid);
                g = getgrgid(filestatus.st_gid);
                printf("%s %s ",p->pw_name,g->gr_name);
                printf("%-6ld ",filestatus.st_size);
                char t[100];
                strcpy(t,ctime(&filestatus.st_mtime));
                t[16]=0;
                printf("%s ",t);
                printf("%s\n",dirc->d_name);
              }
              else
              {
                printf("Error cannot access the file or directory %s\n",dirc->d_name);
                return 1;
              }
            }
          }
          return 1;
        }
      else
      {
          int i=1,l,j,n,k;
          while(arg[i]!=NULL)
          {
            char a_path[200];
            getcwd(a_path,200);
            l = strlen(a_path);
            n = strlen(arg[i]);
            a_path[l]='/';
            for(j=l+1,k=0;k<n;j++,k++)
              a_path[j]=arg[i][k];
            a_path[j]='\0';
            struct stat filestatus;
            struct group *g;
            struct passwd *p;
            if(arg[i][0]=='-')
            {
              i++;
              continue;
            }
            if(stat(a_path,&filestatus) == 0 && S_ISREG(filestatus.st_mode))
            {
              char file_name[200];
              for(j=strlen(a_path)-1;;i--)
                if(a_path[j]=='/')
                  break;
              for(k=j,l=0;l<strlen(a_path);k++,l++)
                file_name[k]=a_path[l];
              if(stat(a_path,&filestatus)>=0)
              {
                printf( (S_ISDIR(filestatus.st_mode)) ? "d" : "-");
                printf( (filestatus.st_mode & S_IRUSR) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWUSR) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXUSR) ? "x" : "-");
                printf( (filestatus.st_mode & S_IRGRP) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWGRP) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXGRP) ? "x" : "-");
                printf( (filestatus.st_mode & S_IROTH) ? "r" : "-");
                printf( (filestatus.st_mode & S_IWOTH) ? "w" : "-");
                printf( (filestatus.st_mode & S_IXOTH) ? "x " : "- ");
                printf("%lu ",filestatus.st_nlink);
                p = getpwuid(filestatus.st_uid);
                g = getgrgid(filestatus.st_gid);
                printf("%s %s ",p->pw_name,g->gr_name);
                printf("%-6ld ",filestatus.st_size);
                char t[100];
                strcpy(t,ctime(&filestatus.st_mtime));
                t[16]=0;
                printf("%s ",t);
                printf("%s\n",file_name);
              }
              else
              {
                printf("Error cannot access the file or directory %s\n",file_name);
                return 1;
              }
              i++;
              continue;
            }
            else
            {
              DIR *d;
              struct dirent *dirc;
              d=opendir(a_path);
              if(d==NULL)
              {
                printf("ls: cannot access : directory or file\n");
                return 1;
              }
              else
              {
                while((dirc = readdir(d))!=NULL)
                {
                    struct stat filestatus;
                    struct passwd *p;
                    struct group *g;
                    char t_path[200];
                    t_path[0]='\0';
                    int l=strlen(a_path),i,j;
                    strcpy(t_path,a_path);
                    t_path[l]='/';
                    int m=strlen(dirc->d_name);
                    for (j=l+1,k=0;k<m;j++,k++)
                      t_path[j]=dirc->d_name[k];
                    t_path[j]='\0';
                    if(stat(t_path,&filestatus)>=0)
                    {
                      printf( (S_ISDIR(filestatus.st_mode)) ? "d" : "-");
                      printf( (filestatus.st_mode & S_IRUSR) ? "r" : "-");
                      printf( (filestatus.st_mode & S_IWUSR) ? "w" : "-");
                      printf( (filestatus.st_mode & S_IXUSR) ? "x" : "-");
                      printf( (filestatus.st_mode & S_IRGRP) ? "r" : "-");
                      printf( (filestatus.st_mode & S_IWGRP) ? "w" : "-");
                      printf( (filestatus.st_mode & S_IXGRP) ? "x" : "-");
                      printf( (filestatus.st_mode & S_IROTH) ? "r" : "-");
                      printf( (filestatus.st_mode & S_IWOTH) ? "w" : "-");
                      printf( (filestatus.st_mode & S_IXOTH) ? "x " : "- ");
                      printf("%lu ",filestatus.st_nlink);
                      p = getpwuid(filestatus.st_uid);
                      g = getgrgid(filestatus.st_gid);
                      printf("%s %s ",p->pw_name,g->gr_name);
                      printf("%-6ld ",filestatus.st_size);
                      char t[100];
                      strcpy(t,ctime(&filestatus.st_mtime));
                      t[16]=0;
                      printf("%s ",t);
                      printf("%s\n",dirc->d_name);
                    }
                    else
                    {
                      printf("Error cannot access the file or directory %s\n",dirc->d_name);
                      return 1;
                    }
                }
                i++;
              }
            }
          }
          return 1;
      }
    }
}
int f_simplels(char **arg)
{
    DIR * d;
    struct dirent *dirc;
    if(arg[1]==NULL)
    {
        char path[200];
        getcwd(path,200);
        d = opendir(path);
        if(d!=NULL)
        {
          while ((dirc = readdir(d))!=NULL)
          {
            if(dirc->d_name[0]!='.')
              printf("%s\n",dirc->d_name);
          }
          return 1;
        }
        else
        {
          printf("ls: cannot access : directory or file\n");
          return 0;
        }
    }
    else
    {
      int i=1,l,j,n,k;
      while(arg[i]!=NULL)
      {
        char a_path[200];
        getcwd(a_path,200);
        l = strlen(a_path);
        n = strlen(arg[i]);
        a_path[l]='/';
        for(j=l+1,k=0;k<n;j++,k++)
          a_path[j]=arg[i][k];
        a_path[j]='\0';
        struct stat file;
        if(stat(a_path,&file) == 0 && S_ISREG(file.st_mode))
        {
          printf("%s\n",arg[i]);
          return 1;
        }
        else
        {
          d = opendir(a_path);
          if(d!=NULL)
          {
            while ((dirc = readdir(d))!=NULL)
            {
              if(dirc->d_name[0]!='.')
                printf("%s\n",dirc->d_name);
            }
          return 1;
          }
          else
          {
            printf("ls: cannot access : directory or file\n");
            return 0;
          }
        }
      }
    }
}

int f_ls(char **arg)
{
  int i,flag=0,k,flag2;
  i=1;
  while(arg[i]!=NULL)
  {
    if(arg[i][0]=='-')
    {
        flag=1;
        if(strcmp(arg[i],"-a")==0)
          flag2=0;
        if(strcmp(arg[i],"-l")==0||strcmp(arg[i],"-al")==0||strcmp(arg[i],"-la")==0)
        {
          flag2=1;
          break;
        }
    }
    i++;
  }
  if(flag==0)
    return f_simplels(arg);
  else
  {
    if(flag2==0)
      return f_lsa(arg);
    else
      return f_lsal(arg);
  }
}
