#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	sig_int();
	sig_quit();
	char buf[256];
	char *argv[50];
	int narg;
	pid_t pid;
	while (1) {
		printf("shell> ");
		gets(buf);
		narg = getargs(buf, argv);
		pid = fork();
		if (pid == 0)
		        execvp(argv[0], argv);
	        else if (pid > 0){
		        sig_int();
		        sig_quit();
		        wait((int *) 0);
		}
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
			argv[narg++] = cmd++;
		while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
			cmd++;
		}
	}
	argv[narg] = NULL;
	return narg;
}

void handlerInt(int signo)
{
   printf("\nSIGINT\n");
   pid_t ppid = getppid();
   kill(ppid, SIGINT);
}
void handlerQuit(int signo)
{
   printf("\nSIGQUIT\ncore dumped\n");
   pid_t ppid = getppid();
   kill(ppid, SIGQUIT);
}
void sig_int()
{
   struct sigaction sig_int;
   sig_int.sa_handler = handlerInt;
   sigfillset(&(sig_int.sa_mask));
   sigaction(SIGINT, &sig_int, NULL);
}
void sig_quit()
{
   struct sigaction sig_quit;
   sig_quit.sa_handler = handlerQuit;
   sigfillset(&(sig_quit.sa_mask));
   sigaction(SIGTSTP, &sig_int, NULL);
}

   