#include <stdio.h>

#define MAX_STAGE 5
#define MAX_RC 30

char map[MAX_RC][MAX_RC];
int map_rows;
int map_cols;

void readMap(int level);
void printMap();

void main(){
while(1)
readMap(1);
printMap();
}

void readMap(int level){
    FILE* map_file;
    int map_level = 0;
    int row=0, col=0;
    int temp_col;
    char temp_char;
    int count = 0;
    int gold_count = 0;
    int store_count = 0;

    // ������ �о stage�� ũ�⸦ �˾Ƴ�
    map_file = fopen("map.txt","r");
    while((temp_char = fgetc(map_file)) != EOF){
        if(temp_char == 'm'|| temp_char == 'e'){
            map_level++;
        }
        if(map_level != level)
            continue;

        temp_col++;

        if(temp_char == '\n'){
            row++;
            if(temp_col > col){
                col = temp_col;
            }
            temp_col=0;
        }
    }

    map_rows = row-1;
    map_cols = col;
    fclose(map_file);

    // map �迭 ������ �ʱ�ȭ �� ��,  ���� ������ �о��

    for(int i=0; i<MAX_RC; i++)
        for(int j=0; j<MAX_RC; j++)
            map[i][j] = ' ';

    map_file = fopen("map.txt","r");
    map_level = 0;
    count = 0;
    for(int i=0; i<map_rows; i++){
        for(int j=0; j<map_cols; j++){
            map[i][j] = fgetc(map_file);
            if(map[i][j] == 'm'){
                map[i][j] = fgetc(map_file);
                map_level++;
            }
            if(map_level != level){
                i=0; j=-1;
                continue;
            }
            if(map[i][j] == 'a')
                map[i][j] = fgetc(map_file);
            if(map[i][i] == 'p')
                map[i][j] = fgetc(map_file);
            if(map[i][j] == '\n' && count ==0){
                count++;
                map[i][j] = fgetc(map_file);
            }
            if(map[i][j] == '\n'){
                for(; j<map_cols-1; j++)
                    map[i][j] = ' ';
                if(map[i][j] == ' ' || map[i][j] == '\n')
                    map[i][j] = '\n';
            }
            if(map[i][j] == '$')
                gold_count++;
            if(map[i][j] == 'O')
                store_count++;
        }
    }
    if(gold_count != store_count){
        printf("$�� 0�� ������ �����ʾ� �����մϴ�.\n");
        exit(1);
    }
    fclose(map_file);
}

void printMap(){
    for(int i=0; i<map_rows; i++){
        for(int j=0; j<map_cols; j++)
            putchar(map[i][j]);
    }
    printf("\n");
}

int getch(void){
    int ch;
    struct termios buf;
    struct termios save;
    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag&=~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}