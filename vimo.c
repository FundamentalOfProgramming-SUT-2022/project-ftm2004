#include<stdio.h>
#include <unistd.h>
#include <io.h>
#include <sys/stat.h>

void error(char a[]);
int createfile();
void createfilewithstr(char* faddress,char* str);
int isFileExists(const char *path);
int validdir(char a[]);
int cat_operation(char fileaddress[]);
int MAX = 1000;

int getRest() {
    for(int i = 0; 1; i++) {
        char c = getchar();
        if(c == '\n') return i;
    }
}
int ar();
FILE *command_file;
int is_ar = 0;
char ar_result[10000];


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
        if (!strcmp(command, "cat")) {
            cat();
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
void error(char a[]) {
    printf("%s\n",a);
}
int createfile() {
    char a[1000], b[1000], inp[1000];
    for(int i = 0; i < 1000; i++) inp[i] = b[i] = NULL;
    scanf("%s", inp);
    if(strcmp(inp, "--file")) {
        error("F!");
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
        error("F!");
        getRest();
        return -1;
    }
    scanf("%s", path);
    scanf("%s", inp);
    if(strcmp(inp, "--str")) {
        error("F!");
        getRest();
        return -1;
    }
    scanf("%s", str);
    scanf("%s", inp);
    if(strcmp(inp, "--pos")) {
        error("!F");
        getRest();
        return -1;
    }
    scanf("%d:%d", &line, &col);
    //printf("%s %s \n", path, str);
    //printf("%d+%d\n", line, col);
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        error("not valid path");
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
        error("not valid pos");
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





int cat(){
    int catc=2;
    char fileaddress[MAX];
    int valid_input = file_input(fileaddress, catc);

    if (valid_input == -1)
    {
        return -1;
    }

    track_changes(fileaddress);

    int valid_action = cat_operation(fileaddress);
    if (valid_action == -1)
    {
        undo_action(fileaddress);
        return -1;
    }

    return 0;
}

int cat_operation(char fileaddress[])
{
    // does directory exist
    if (!dir_exist(fileaddress))
    {
        error("directory doesn't exist");
        return -1;
    }

    // does file exist
    FILE *f = fopen(fileaddress, "r");
    if (f == NULL)
    {
        error("file doesn't exist");
        getRest();
        return -1;
    }

    char line[1000];

    while (fgets(line, 1000, f) != NULL)
    {
        if (!is_ar)
            printf("%s", line);
        else
            sprintf(ar_result + strlen(ar_result), line);
    }
    if (!is_ar)
        printf("\n");
    fclose(f);
    return 0;
   }








