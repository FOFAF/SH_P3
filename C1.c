#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
        char buf[256];
        char *argv[50];
        int narg;
        pid_t pid;
        while (1) {
//              int fds[2];
//              pipe(fds);


                printf("shell> ");
                gets(buf);
                if(!strcmp(buf,"exit"))
                        return 0;
                narg = getargs(buf, argv);
                pid = fork();
                if (pid == 0)
                        execvp(argv[0], argv);
                else if (pid > 0)
                        wait((int *) 0);
                        //write(fds[1] , str, sizeof(str));
                        //if(strcmp(fds,"exit")
                        //      return 0;
                else
                        perror("fork failed");
                }
}

int getargs(char *cmd, char **argv)
{
        int narg = 0;
        while (*cmd) {
                if (*cmd == ' ' || *cmd == '\t')
                        *cmd++ = '\0';
                else {
                        argv[narg++] = cmd++; // space char ex
                while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
                        cmd++;
                        //if(strcmp(*cmd,"exit"){
                        //      read(fds[0] , "exit" , BUF_SIZE);
                        //              puts(buf);
                        //}
                }
        }
        argv[narg] = NULL;
}