#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

char* pwd();
void ls(int argc, char *argv[]){
        DIR* dir;
        if(argc < 2)
                dir = opendir(".");
        else if (argc == 2)
                dir = opendir(argv[1]);
        if(dir == NULL){
                printf("디렉토리를 열수 없습니다.\n");
                return;
        }
        struct dirent *entry;
        while((entry=readdir(dir))!=NULL){
                if(strcmp(entry->d_name,".") == 0
                || strcmp(entry->d_name,"..") == 0)continue;
                printf("%s\n",entry->d_name);
        }
        closedir(dir);
}
char* pwd(){
        char strBuffer[250] = { 0, };
        char *pstrBuffer = NULL;

        pstrBuffer = getcwd( strBuffer, 250 );
        printf("%s\n",pstrBuffer);
        return pstrBuffer;
}
bool cd(int argc, char* argv[]){
        char strBuffer[250] = { 0, };
        char *strChangeDir = argv[1];

        int nResult = chdir( strChangeDir );
        return nResult+1;
}

void Mkdir(int argc, char* argv[]){
        umask(0000);
        char *strFolderPath = argv[1];
        if(argc < 2){ printf("error\n"); return; }
         mkdir(strFolderPath,0777);
}

void Rmdir(int argc, char *argv[] ){
        char *strFolderPath = argv[1];
        if(argc < 2){ printf("error\n"); return; }
        rmdir(strFolderPath);
}

void ln(int argc, char *argv[])
{
        char cmd;
        char *src;
        char *target;
        if (argc < 3) {
                fprintf(stderr, "Usage: file_link [l,u,s] ...\n");
                fprintf(stderr, " file_link l[ink] src target\n");
                fprintf(stderr, " file_link u[nlink] filename\n");
                fprintf(stderr, " file_link s[ymlink] src target\n");
                exit(1);
        }
        cmd = (char) *argv[1];
        if ( cmd == 'l' ) {
                if (argc < 3) {
                        fprintf(stderr, "file_link l src target [link]\n");
                        exit(1);
                }
                src = argv[2];
                target = argv[3];
                if (link(src, target) < 0) {
                        perror("link");
                        exit(1);
                }
        }
        else if (cmd == 's') {
                if (argc < 4) {
                        fprintf(stderr, "file_link l src target [link]\n");
                        exit(1);
                }
                src = argv[2];
                target = argv[3];
                if (symlink(src, target) < 0) {
                        perror("symlink");
                        exit(1);
                }
        }
        else if (cmd == 'u') {
                src = argv[2];
                if (unlink(src) < 0) {
                        perror("unlink");
                        exit(1);
                }
        }
        else
                fprintf(stderr, "Unknown command...\n");
}

void cp(int argc, char *argv[])
{
        FILE *src;
        FILE *dst;
        char ch;
        int count = 0;
        printf("CP\n");
        if (argc < 3) {
                printf("Usage: file_copy source_file destination_file\n");
                exit(1);
        }
        if ( (src = fopen(argv[1], "r")) == NULL ) {
                perror("fopen: src");
                exit(1);
        }
        if ( (dst = fopen(argv[2], "w")) == NULL ) {
                perror("fopen: dst");
                exit(1);
        }
        while ( !feof(src) ) {
                ch = (char) fgetc(src);
                if ( ch != EOF )
                        fputc((int)ch, dst);
                count++;
        }
        fclose(src);
        fclose(dst);
        printf("CPE\n");
}

void rm(char* path )
{
        int nResult = remove( path );
        if( nResult == 0 )
                printf( "파일 삭제 성공" );
        else if( nResult == -1 )
                perror( "파일 삭제 실패" );
}

void mv(int argc, char *argv[]){
        cp(argc, argv);
        rm(argv[1]);
}
void cat(char *argv[]){
    FILE* fp = fopen(argv[1], "r");
    char buffer[100000] = { 0, };

    fread(buffer, 1, 100000, fp);
    printf("%s", buffer);

    fclose(fp);
}
int main(int argc, char *argv[]){
        char buf[256];
        char argv2[256];
        char *argv3;
        char *str[50];
        char CD[50]="> ";
        int count = 0;
        int narg = 0;
        while (1) {
                *buf = NULL;
                *argv2 = NULL;
                argv3 =  NULL;
                *str = NULL;
                count = 0;
                narg = 0;
                char shell[50] = "shell";
                        strcat(shell,CD);
                printf("%s",shell);
                gets(buf);
                strcpy(argv2,buf);
                char *argv3 = argv2;
                while (buf[count]) {
                        if (buf[count] == ' ' || buf[count] == '\t'){
                                char a[2] = {buf[count],'\0'};
                                char* temp = strtok_r(argv3,a,&argv3);
                                str[narg++] = temp;
                                str[narg] = argv3;
                        }
                        count++;
                }
                if(narg == 0)
                        str[narg] = argv3;
                if(strcmp(str[0],"ls") == 0)
                        ls(narg+1,str);
                else if(strcmp(str[0],"pwd") == 0)
                        pwd();
                else if(strcmp(str[0],"cd") == 0){
                        if(cd(narg+1,str))
                                strcat(strcpy(CD,str[1]),"> ");
                }
                else if(strcmp(str[0],"mkdir") == 0)
                        Mkdir(narg+1,str);
                else if(strcmp(str[0],"rmdir") == 0)
                        Rmdir(narg+1,str);
                else if(strcmp(str[0],"ln") == 0)
                        ln(narg+1,str);
                else if(strcmp(str[0],"cp") == 0)
                        cp(narg+1,str);
                else if(strcmp(str[0],"rm") == 0)
                        rm(str[1]);
                else if(strcmp(str[0],"mv") == 0)
                        mv(narg+1,str);
                else if(strcmp(str[0],"cat") == 0)
                        cat(str);
        }
        return 0;
}


