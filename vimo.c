#include<stdio.h>
#include <unistd.h>
#include <io.h>
#include <sys/stat.h>

void eror(char a[]);
int createfile();
void createfilewithstr(char* faddress,char* str);
int isFileExists(const char *path);
int validdir(char a[]);

int MAX = 1000;

int getRest() {
    for(int i = 0; 1; i++) {
        char c = getchar();
        if(c == '\n') return i;
    }

}

int main() {
    while(1) {
        char command[1000];
        printf("> ");
        scanf("%s", command);
        if (!strcmp(command, "createfile")) {
            createfile();
        }
        if (!strcmp(command, "insertstr")) {
            insertstr();
        }

    }
}
int isFileExists(const char *path)
{
    // Check for file existence
    if (access(path, F_OK) == -1)
        return 0;

    return 1;
}
void eror(char a[]) {
    printf("%s\n",a);
}
int createfile() {
    char a[1000], b[1000], inp[1000];
    for(int i = 0; i < 1000; i++) inp[i] = b[i] = NULL;
    scanf("%s", inp);
    if(strcmp(inp, "--file")) {
        eror("F!");
        getRest();
        return -1;
    }
    scanf("%s", inp);
    int sz = 0, len = 0;
    for(int i = 0; i < sizeof(a); i++) {
        if(inp[i] == NULL){
            len = i - 1;
            //printf("i = %d\n", i);
            break ;
        }
        if(inp[i] == '/') {

            for(int j = 0; j < sz; j++) {
                b[j] = NULL;
            }
            sz = 0;
            if(!isFileExists(a)) {
                mkdir(a);
            }
        }
        else {
            b[sz++] = inp[i];
        }
        a[i] = inp[i];
    }
    inp[len++] = '.';
    inp[len++] = 't';
    inp[len++] = 'x';
    inp[len++] = 't';
    fopen(inp, "w");
    return 0;

}
void createfilewithstr(char* faddress,char* str) {
//    printf("%c", )
    FILE *fp = NULL;
    fp = fopen(faddress ,"a");
}

//iansertstr(char* argv[3],char* argv[5],char* argv[5]); {

//}


int insertstr() {
    char inp[MAX], path[MAX], str[MAX], pos[MAX], ans[MAX];
    for(int i = 0; i < MAX; i++){
        inp[i] = path[i] = str[i] = pos[i] = ans[i] = '\0';
    }
    int line, col, n = 0;
    //insertstr –file /root/dir1/dir2/file.txt –str Salam –pos 2:5
    scanf("%s", inp);
    if(strcmp(inp, "--file")) {
        eror("F!");
        getRest();
        return -1;
    }
    scanf("%s", path);
    scanf("%s", inp);
    if(strcmp(inp, "--str")) {
        eror("F!");
        getRest();
        return -1;
    }
    scanf("%s", str);
    scanf("%s", inp);
    if(strcmp(inp, "--pos")) {
        eror("!F");
        getRest();
        return -1;
    }
    scanf("%d:%d", &line, &col);
    //printf("%s %s \n", path, str);
    //printf("%d+%d\n", line, col);
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        eror("not valid path");
        getRest();
        return -1;
    }
    int check = 0, flag = 1;
    for(int line_counter = 1;  flag; line_counter++) {
        for(int col_counter = 0; 1; col_counter++) {
            char c = fgetc(file);
            if(c == EOF) {
                flag = 0;
                break ;
            }
            //printf("c = %c\n", c);
            if(line_counter == line && col_counter == col) {
                check = 1;
                for(int i = 0; str[i] != NULL; i++) {
                    ans[n++] = str[i];
                }
            }

            ans[n++] = c;
            if(c == '\n') break ;
            //if(line_counter > 2 || col_counter > 20) return -1;
        }

    }
    if(check == 0) {
        eror("not valid pos");
        getRest();
        return -1;
    }
    fclose(file);
    file = fopen(path, "w");
    fprintf(file, "%s", ans);
    fclose(file);
    return 0;
}
//insertstr --file root/ah.txt --str khoobi --pos 1:5







