#include<stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

void error(char a[]);
int createfile();
void createfilewithstr(char* faddress,char* str);
int isFileExists(const char *path);
int validdir(char a[]);
int MAX = 100;
int cat();
int removeser();
int insertstr();

int p, inplen;
char inp[100];
char q[100];

void error(char a[]) {
    printf("%s\n",a);
}
void readstring() {
    for(int i = 0; i < 100; i++) inp[i] = '\0';
    inplen = 0;
    if(q[p] == '\0') return ;
    int sum = 1;
    if(q[p] == '\"'){
        p++;
        while(q[p] != '\"') {
            if(q[p] == '\\' && q[p+1] == '\"') {
                inp[inplen++] = '\"';
                p+=2;
                continue ;
            }
            if(q[p] == '\\' && q[p+1] == '\\' && q[p+2] == 'n') {
                inp[inplen++] = '\\';
                inp[inplen++] = 'n';
                p+=3;
                continue ;
            }
            if(q[p] == '\\' && q[p+1] == 'n') {
                inp[inplen++] = '\n';
                p+=2;
                continue ;
            }
            inp[inplen++] = q[p++];
        }
        p++;
    }
    else {
        while(q[p] != ' ' && q[p] != '\0') {
            if(q[p] == '\\' && q[p+1] == '\\' && q[p+2] == 'n') {
                inp[inplen++] = '\\';
                inp[inplen++] = 'n';
                p+=3;
                continue ;
            }
            if(q[p] == '\\' && q[p+1] == 'n') {
                inp[inplen++] = '\n';
                p+=2;
                continue ;
            }
            inp[inplen++] = q[p++];
        }
    }
    p++;
    return ;
}
void copyinp(char a[]) {
    for(int i = 0; i < MAX; i++) {
        a[i] = inp[i];
    }
}
int readint() {
    int ans = 0;
    if(q[p] < '0' || q[p] > '9') {
        return -1;
    }
    while('0' <= q[p] && q[p] <= '9') {
        ans = ans * 10 + q[p++] - '0';
    }
    p++;
    return ans;
}
int isFileExists(const char *path)
{
    // Check for file existence
    if (access(path, F_OK) == -1)
        return 0;

    return 1;
}
int createfile() {
    char a[100], b[100];
    for(int i = 0; i < 100; i++) a[i] = b[i] = '\0';
    readstring();
    if(strcmp(inp, "--file")) {
        error("not valid");
        return -1;
    }
    readstring();
    int sz = 0, len = 0;
    for(int i = 0; i < sizeof(a); i++) {
        if(inp[i] == '\0'){
            len = i;
            //printf("i = %d\n", i);
            break ;
        }
        if(inp[i] == '/') {

            for(int j = 0; j < sz; j++) {
                b[j] = '\0';
            }
            sz = 0;
            if(!isFileExists(a)) {
                mkdir(a,0777);
            }
        }
        else {
            b[sz++] = inp[i];
        }
        a[i] = inp[i];
    }
    /*inp[len++] = '.';
    inp[len++] = 't';
    inp[len++] = 'x';
    inp[len++] = 't';*/
    fopen(inp, "w");
    return 0;

}
void createfilewithstr(char* faddress,char* str) {
//    printf("%c", )
    FILE* fp = '\0';
    fp = fopen(faddress ,"a");
}


int insertstr() {
    char path[MAX], str[MAX], pos[MAX], ans[MAX];
    for(int i = 0; i < MAX; i++){
        inp[i] = path[i] = str[i] = pos[i] = ans[i] = '\0';
    }
    int line = -1, col = -1, n = 0;
    readstring();
    if(strcmp(inp, "--file")) {
        error("not valid");
        return -1;
    }
    readstring(); copyinp(path);
    readstring();
    if(strcmp(inp, "--str")) {
        error("not valid --str expexted");
        return -1;
    }
    readstring(); copyinp(str);
    readstring();
    if(strcmp(inp, "--pos")) {
        error("not valid --pos expected");
        return -1;
    }
    line = readint();
    if(line == -1) {
        error("not valid");
        return -1;
    }
    if(q[p-1] != ':') {
        error("not valid");
        return -1;
    }
    col = readint();
    if(col == -1) {
        error("not valid");
        return -1;
    }
    //printf("%s %s %d %d\n", path, str, line , col);
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        error("not valid path.");
        return -1;
    }
    int check = 0, flag = 1;
    for(int line_counter = 1;  flag; line_counter++) {
        for(int col_counter = 0; 1; col_counter++) {
            char c = fgetc(file);
            //printf("c = %c\n", c);
            if(line_counter == line && col_counter == col) {
                check = 1;
                for(int i = 0; str[i] != '\0'; i++) {
                    ans[n++] = str[i];
                }
            }
            if(c == EOF) {
                flag = 0;
                break ;
            }
            ans[n++] = c;
            if(c == '\n') break ;
            //if(line_counter > 2 || col_counter > 20) return -1;
        }

    }
    if(check == 0) {
        error("not valid pos.");
        return -1;
    }
    fclose(file);
    file = fopen(path, "w");
    fprintf(file, "%s", ans);
    fclose(file);
    return 0;
}


int cat() {
    char path[MAX];
    for(int i = 0; i < MAX; i++) path[i] = NULL;
    readstring();
    if(strcmp(inp, "--file")!=0) {
        error("expected --file");
        return -1;
    }
    readstring(); copyinp(path);
    FILE* file;
    char ch;
    file = fopen(path, "r");
    if (file == NULL) {
        error("File doesn't exist.");
        return -1;
    }
    do{
        ch = fgetc(file);
        printf("%c", ch);
    } while (ch != EOF);
    printf("\n");
    fclose(file);
    return 0;


}

int main() {
    while(1) {
        char command[MAX];
        for(int i = 0; i < MAX; i++) q[i] = command[i] = '\0';
        printf("> ");
        scanf("%s", command);
        getchar();
        scanf("%[^\n]", q); p=0;
        if (!strcmp(command, "exit")) {
            break ;
        }
        if (!strcmp(command, "createfile")) {
            createfile();
        }
        if (!strcmp(command, "insertstr")) {
            insertstr();
        }
        if (!strcmp(command, "cat")) {
            cat();
        }

    }
    printf("exited!");
}

