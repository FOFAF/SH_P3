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
		printf("shell> ");
		gets(buf);
		narg = getargs(buf, argv);
		pid = fork();
		if (pid == 0)
			execvp(argv[0], argv);
		else if (pid > 0)
			wait((int *) 0);
		else
			perror("fork failed");
		}
}

int getargs(char *cmd, char **argv)
{
	int narg = 0;
	int count = 0;
	while (*cmd) {
		if (cmd[count] == '|' || cmd[count] == '<' || cmd[count] == '>')
			 char* temp = strtok_s(argv,cmd[count], &argv);
			  printf("잘린 문자열 : %s\n", temp);
		else {
			argv[narg++] = cmd++;
		while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
			cmd++;
		}
		count++;
	}
	argv[narg] = NULL;
	return narg;
}
/////////////////////////////////////////////////////
int main()
{
	char buf[256];
	char *argv[50];
	int narg;
	pid_t pid;
	while (1) {
		printf("shell> ");
		gets(buf);
		//narg = getargs(buf, argv);
		pid = fork();
		if (pid == 0)
			getargs(buf, argv);
		else if (pid > 0)
			wait((int *) 0);
		else
			perror("fork failed");
		}
}

int getargs(char *cmd, char **argv)
{
	int narg = 0;
	File *A = null;
	File *B = null;
	while (*cmd) {
		if(*(cmd+1) == '|' || *(cmd+1) == '<' || *(cmd+1) == '>'){
			char buf[256];
			A = popen(*argv,"r");
			cmd++;
			*argv=NULL;
			narg=0;
			while(*(cmd+1) == '|' || *(cmd+1) == '<' || *(cmd+1) == '>')
				argv[narg++] = cmd++;
			B = popen(*argv,"w");
			while(fgets(buf, 256, A) != NULL)
				fputs(buf, B);
			pclose(A);
			pclose(B);
			continue;
		}
		argv[narg++] = cmd++;
		while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
			cmd++;
		}
	}
	argv[narg] = NULL;
	return narg;
}

void AAA(char* buf){
	while (*cmd) {
		if(*cmd == '|' || *cmd == '<' || *cmd == '>'){
			A = popen(*argv,"r");
			B = popen(*
		}
	}
}
1. 반복 문자열 잘라서 저장
2. 4줄 실행
3. A = B;
4. 