#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ISBACKGROUND = 0;
int main()
{
   char buf[256];
   char *argv[50];
   int narg, status;
   pid_t pid;
   while (1) {
      printf("shell> ");
      gets(buf);
      narg = getargs(buf, argv);
      pid = fork();
      if (pid == 0){
         if(ISBACKGROUND){
              printf("background process.\n");
              execvp(argv[0], argv);
         }
           }   
           else if (pid > 0)
         
         if(ISBACKGROUND)
         pid = wait(&status);
      else
         perror("fork failed");
      }
}

int getargs(char *cmd, char **argv)
{
   int narg = 0;
   while (*cmd) {
      if (*cmd == ' ' || *cmd == '\t'|| *cmd == '&'){
         *cmd++ = '\0';
         if (*cmd == '&')
         ISBACKGROUND = 1;
      }
      else {
         argv[narg++] = cmd++;
      while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
         cmd++;
      }
   }
   argv[narg] = NULL;
   return narg;
}