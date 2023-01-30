#include<stdio.h>
#include <unistd.h>
#include <io.h>
#include <sys/stat.h>

void eror(char a[]);
int createfile();
void createfilewithstr(char* faddress,char* str);
int isFileExists(const char *path);
int validdir(char a[]);

int main() {
    while(1) {
        char command[1000];
        printf("> ");
        scanf("%s", command);
        if (!strcmp(command, "createfile")) {
            createfile();
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

