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
const int MAX = 100;
int cat();
int removeser();
int insertstr();
void comparebyline();
int p, inplen, clipboardpointer;
char inp[100], sub1[100], sub2[100];
char q[100];
char clipboard[100];

void error(char a[]) {
    printf("%s\n",a);
}
int getsize(char a[]) {
    for(int i = 0; i < MAX; i++) {
        if(a[i] == '\0') {
            return i;
        }
    }
}
void readstring() {
    for(int i = 0; i < MAX; i++) inp[i] = '\0';
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
void readpattern() {
    for(int i = 0; i < MAX; i++) inp[i] = '\0';
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
            if(q[p] == '*') {
                inp[inplen++] = (char) 255;
                p+=1;
                continue ;
            }
            if(q[p] == '\\' && q[p+1] == '*') {
                inp[inplen++] = '*';
                p+=2;
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
            if(q[p] == '*') {
                inp[inplen++] = (char) 255;
                p+=1;
                continue ;
            }
            if(q[p] == '\\' && q[p+1] == '*') {
                inp[inplen++] = '*';
                p+=2;
            }
            inp[inplen++] = q[p++];
        }
    }
    p++;
    return ;
}
void getsubstring(char a[],int l,int r,int t) {
    for(int i = 0; i < MAX; i++) {
        if(t == 1) sub1[i] = '\0';
        else sub2[i] = '\0';
    }
    for(int i = l; i < r; i++) {
        if(t == 1) sub1[i - l] = a[i];
        else sub2[i - l] = a[i];
    }
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
int checkpattern(char a[], char b[]) {
    int dp[MAX][MAX];
    for(int i = 0; i < MAX; i++) for(int j = 0; j < MAX; j++) dp[i][j] = 0;
    dp[0][0] = 1;


    for(int i = 0; i < getsize(a); i++) {
        for(int j = 0; j < getsize(b); j++) {
            if(a[i] == b[j] && dp[i][j]) {
                dp[i + 1][j + 1] = 1;
            }
            if(a[i] != ' ' && b[j] == (char) 255 && (dp[i][j + 1] || dp[i][j])) {
                dp[i + 1][j + 1] = 1;
            }
            if(b[j] == (char) 255 && dp[i+1][j]) {
                dp[i + 1][j + 1] = 1;
            }

        }
    }
    return dp[getsize(a)][getsize(b)];
}
int cat() {
    char path[MAX];
    for(int i = 0; i < MAX; i++) path[i] = '\0';
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
int createfile() {
    char a[MAX], b[MAX];
    for(int i = 0; i < MAX; i++) a[i] = b[i] = '\0';
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

            break ;
        }
        if(inp[i] == '/') {

            for(int j = 0; j < sz; j++) {
                b[j] = '\0';
            }
            sz = 0;
            if(!isFileExists(a)) {
//                mkdir(a,0777);
            }
        }
        else {
            b[sz++] = inp[i];
        }
        a[i] = inp[i];
    }

    fopen(inp, "w");
    return 0;

}
void createfilewithstr(char* faddress,char* str) {

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

    FILE* file = fopen(path, "r");
    if(file == NULL) {
        error("not valid path.");
        return -1;
    }
    int check = 0, flag = 1;
    for(int line_counter = 1;  flag; line_counter++) {
        for(int col_counter = 0; 1; col_counter++) {
            char c = fgetc(file);

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

int pastestr() {
    char path[MAX], pos[MAX], ans[MAX];
    for(int i = 0; i < MAX; i++){
        inp[i] = path[i] = pos[i] = ans[i] = '\0';
    }
    int line = -1, col = -1, n = 0;
    readstring();
    if(strcmp(inp, "--file")) {
        error("not valid");
        return -1;
    }
    readstring(); copyinp(path);
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

    FILE* file = fopen(path, "r");
    if(file == NULL) {
        error("not valid path.");
        return -1;
    }
    int check = 0, flag = 1;
    for(int line_counter = 1;  flag; line_counter++) {
        for(int col_counter = 0; 1; col_counter++) {
            char c = fgetc(file);

            if(line_counter == line && col_counter == col) {
                check = 1;
                for(int i = 0; clipboard[i] != '\0'; i++) {
                    ans[n++] = clipboard[i];
                }
            }
            if(c == EOF) {
                flag = 0;
                break ;
            }
            ans[n++] = c;
            if(c == '\n') break ;

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
int cutstr() {
    int filepointer = 0;
    char a[MAX], path[MAX], filetext[MAX];
    for(int i = 0; i < MAX; i++) filetext[i] = path[i] = a[i] = '\0';
    readstring();
    if(strcmp(inp, "--file")) {
        error("expected --file");
        return -1;
    }
    readstring(); copyinp(path);
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        error("not valid path.");
        return -1;
    }
    readstring();
    if(strcmp(inp, "--pos")) {
        error("expected --file");
        return -1;
    }
    int line = -1, col = -1;
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
    readstring();
    if(strcmp(inp, "--size")) {
        error("expected --size");
        return -1;
    }
    int size = readint();
    if(size == -1) {
        error("size must be a number");
        return -1;
    }
    int check = 0, flag = 1;
    for(int line_counter = 1;  flag; line_counter++) {
        for(int col_counter = 0; 1; col_counter++) {
            char c = fgetc(file);
            filetext[filepointer++] = c;
            if(c == EOF) {
                flag = 0;
                break ;
            }
            if(line_counter == line && col_counter == col) {
                int counter = 0;
                filetext[filepointer--] = '\0';
                while(size--) {
                    a[counter++] = c;
                    //if(c == '\n') size++;
                    c = fgetc(file);
                    if(c == EOF) {
                        break ;
                    }
                }
                if(c != EOF) {
                    check = 1;
                    for(int i = 0; i < MAX; i++) {
                        if(i < counter) {
                            clipboard[i] = a[i];
                        }
                        else {
                            clipboard[i] = '\0';
                        }
                    }
                    do {
                        filetext[filepointer++] = c;
                        c = fgetc(file);
                    } while(c != EOF);
                    clipboardpointer = counter;
                }
                flag = 0;
                break ;
            }

        }
    }
    fclose(file);
    if(check == 0) {
        error("not valid position or size");
        return -1;
    }
    file = fopen(path, "w");
    fprintf(file, "%s", filetext);
    fclose(file);
    return 0;

}
int copystr() {
    char a[MAX], path[MAX];
    for(int i = 0; i < MAX; i++) path[i] = a[i] = '\0';
    readstring();
    if(strcmp(inp, "--file")) {
        error("expected --file");
        return -1;
    }
    readstring(); copyinp(path);
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        error("not valid path.");
        return -1;
    }
    readstring();
    if(strcmp(inp, "--pos")) {
        error("expected --file");
        return -1;
    }
    int line = -1, col = -1;
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
    readstring();
    if(strcmp(inp, "--size")) {
        error("expected --size");
        return -1;
    }
    int size = readint();
    if(size == -1) {
        error("size must be a number");
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
            if(line_counter == line && col_counter == col) {
                int counter = 0;
                while(size--) {
                    a[counter++] = c;

                    c = fgetc(file);
                    if(c == EOF) {
                        break ;
                    }
                }
                if(c != EOF) {
                    check = 1;
                    for(int i = 0; i < MAX; i++) {
                        if(i < counter) {
                            clipboard[i] = a[i];
                        }
                        else {
                            clipboard[i] = '\0';
                        }
                    }
                    clipboardpointer = counter;
                }
                flag = 0;
                break ;
            }

        }
    }
    if(check == 0) {
        error("not valid position or size");
        return -1;
    }
    return 0;
}
int removestr() {
    int filepointer = 0;
    char path[MAX], filetext[MAX];
    for(int i = 0; i < MAX; i++) filetext[i] = path[i] = '\0';
    readstring();
    if(strcmp(inp, "--file")) {
        error("expected --file");
        return -1;
    }
    readstring(); copyinp(path);
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        error("not valid path.");
        return -1;
    }
    readstring();
    if(strcmp(inp, "--pos")) {
        error("expected --file");
        return -1;
    }
    int line = -1, col = -1;
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
    readstring();
    if(strcmp(inp, "--size")) {
        error("expected --size");
        return -1;
    }
    int size = readint();
    if(size == -1) {
        error("size must be a number");
        return -1;
    }
    readstring();
    if(strcmp(inp, "--b") && strcmp(inp, "--f")) {
        error("flag must be --b or --f");
        return -1;
    }
    int check = 0, flag = 1;
    for(int line_counter = 1;  flag; line_counter++) {
        for(int col_counter = 0; 1; col_counter++) {

            char c = fgetc(file);
            filetext[filepointer++] = c;
            if(c == EOF) {
                flag = 0;
                break ;
            }
            if(line_counter == line && col_counter == col) {
                int counter = 0;
                if(!strcmp(inp, "--f")){
                    filetext[filepointer--] = '\0';
                    size--;
                    while(size--) {


                        c = fgetc(file);
                        if(c == EOF) {
                            break ;
                        }
                    }
                    if(c != EOF) {
                        check = 1;
                    }
                }
                else {
                    while(size-- && filepointer >= 0) {
                        if(filetext[filepointer] == '\n') {

                        }
                        filetext[filepointer--] = '\0';
                    }
                    if(filepointer >= 0) {
                        check = 1;
                    }
                }
                flag = 0;
                break ;
            }

        }
    }
    char c = fgetc(file);
    while(c != EOF) {
        filetext[filepointer++] = c;
        c = fgetc(file);
    }
    fclose(file);
    if(check == 0) {
        error("not valid position or size");
        return -1;
    }
    file = fopen(path, "w");
    if(check == 1) {
        fprintf(file, "%s", filetext);
    }
    fclose(file);
    return 0;
}
int find() {
    int type = 0 , n, startingstr[MAX], startingtext[MAX], vaje[MAX], ebi[MAX], ebicounter = 0, strcounter = 0, textcounter = 0, textpointer = 0;
    char path[MAX], str[MAX], text[MAX];
    for(int i = 0; i < MAX; i++) path[i] = str[i] = text[i] = '\0', startingtext[i] = startingstr[i] = vaje[i] = ebi[i] = 0;
    readstring();
    if(strcmp(inp, "--str")) {
        error("expected --file");
        return -1;
    }
    readpattern(); copyinp(str);
    readstring();
    if(strcmp(inp, "--file")) {
        error("expected --file");
        return -1;
    }
    readstring(); copyinp(path);
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        error("not valid path.");
        return -1;
    }
    readstring();
    if(!strcmp(inp, "--count")) {
        type = 1;
    }
    if(!strcmp(inp, "--at")) {
        type = 2;
        n = readint();
        if(n == -1) {
            error("not valid number");
        }
    }
    if(!strcmp(inp, "--byword")) {
        type = 3;
    }
    if(!strcmp(inp, "--all")) {
        type = 4;
        readstring();
        if(strcmp(inp, "--byword")) {
            error("expected --byword");
            return -1;
        }
    }
    char c = fgetc(file);
    while(c != EOF) {
        if(c == '\n') c = ' ';
        text[textpointer++] = c;
        c = fgetc(file);
    }
    for(int i = 0; 1; i++) {
        if(text[i] == '\0') {
            startingtext[textcounter++] = i + 1;
            break ;
        }
        if(text[i] == ' ') {
           startingtext[textcounter++] = i + 1;
        }
        else if(i == 0) {
            startingtext[textcounter++] = i;
        }
    }
    for(int i = 0; 1; i++) {
        if(str[i] == '\0') {
            startingstr[strcounter++] = i + 1;
            break ;
        }
        if(str[i] == ' ') {
           startingstr[strcounter++] = i + 1;
        }
        else if(i == 0) {
            startingstr[strcounter++] = i;
        }
    }
    vaje[0] = 1;
    for(int i = 1; i < textcounter; i++) {
        vaje[i] = vaje[i-1] + (text[startingtext[i] + 1] != ' ');
    }
    for(int i = 0; i < textcounter - 1; i++) {
        int check = 1;
        if(str[0] == ' ' && (startingtext[i] == 0 || text[startingtext[i] - 1] != ' ')) {
            check = 0;
        }
        for(int j = 0; j < strcounter - 1; j++) {
            if(i + j >= textcounter - 1) {
                check = 0;
                break ;
            }
            getsubstring(text, startingtext[i + j], startingtext[i + j + 1] - 1, 1);
            getsubstring(str, startingstr[j], startingstr[j + 1] - 1, 2);
            if((i == 0 && j == 0) || 1) {

            }
            if(checkpattern(sub1, sub2) == 0) {

                check = 0;
            }
        }
        if(check == 1) {
            ebi[ebicounter++] = i;
        }
    }
    if(type == 0) {
        if(ebicounter == 0) {
            printf("-1\n");
        }
        else {
            printf("%d\n", startingtext[ebi[0]]);
        }
        return 0;
    }
    if(type == 1){
        printf("%d\n", ebicounter);
        return 0;
    }
    if(type == 2) {
        if(n >= ebicounter) {
            printf("-1\n");
        }
        else {
            printf("%d\n", startingtext[ebi[n]]);
        }
    }
    if(type == 3) {
        if(ebicounter == 0) {
            printf("-1\n");
        }
        else{
            printf("%d\n", vaje[ebi[0]]);
        }
    }
    if(type == 4) {
        printf("starting words : ");
        for(int i = 0; i < ebicounter; i++) {
            printf("%d ", vaje[ebi[i]]);
        }
        printf("\n");
    }

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
        if (!strcmp(command, "copystr")) {
            copystr();
        }
        if (!strcmp(command, "pastestr")) {
            pastestr();
        }
        if (!strcmp(command, "cutstr")) {
            cutstr();
        }
        if(!strcmp(command, "removestr")) {
            removestr();
        }
        if(!strcmp(command, "find")) {
            find();
        }
         if(!strcmp(command, "compare")) {
            comparebyline();
        }


    }
    printf("exited!");
}



void comparebyline() {
    char *address1 = (char*) calloc(50, 1);
    char *address2 = (char*) calloc(50, 1);
    sscanf(q, "%s %s", address1, address2);
    FILE *file1 = fopen(address1, "r");
    FILE *file2 = fopen(address2, "r");
    char line1[256];
    char line2[256];
    int lineCnt = 1;
    while (fgets(line1, sizeof(line1), file1) != NULL &&
        fgets(line2, sizeof(line2), file2) != NULL) {
        // Compare the lines
        if (strcmp(line1, line2) != 0) {
            printf("============ #%d ============\n", lineCnt);
            printf("%s", line1);
            printf("%s", line2);
        }
            lineCnt++;
    }

    FILE *biggerOne;
    if (feof(file1))
        if (feof(file2)) return;
    else biggerOne = file2;
    else biggerOne = file1;
    int startLine = lineCnt--;
    char *remainder = (char*) calloc(1000, 1);
    while (fgets(line1, sizeof(line1), biggerOne)) {
        strcat(remainder, line1);
        lineCnt++;
    }
    printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n", startLine, lineCnt);
    puts(remainder);
    fclose(file1);
    fclose(file2);
    free(remainder);
    free(address1);
    free(address2);
}
