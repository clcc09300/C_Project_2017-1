#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termio.h>

#define MAX_STAGE 5
#define MAX_RC 30

char map[MAX_RC][MAX_RC];
int map_rows;
int map_cols;

char user_name[10];
clock_t start, end;   // �������� ���� �� �� �ð�
float t1,t2,t3,t4,t5; // ���������� Ŭ���� �ð�
int Px,Py; // �÷��̾� ��ġ
int stage = 1; // ���� ��������
int undo_x[5] = {0};
int undo_count=0;
int slot_x[MAX_RC] = {0};
int slot_y[MAX_RC] = {0};
int slot_count=0;
int gold_x[MAX_RC] = {0};
int gold_y[MAX_RC] = {0};
int gold_count=0;

void readMap(int level);
void printMap();
void displayHelp();
int getch();
void screen_clear();
void move(char dir);

void main(){
    char cmd;
    while(1){
        printf("input name : ");
        gets(user_name);
        user_name[10] = '\0';
        screen_clear();
        while(1){
            readMap(stage);
            start = clock();
            while(1){
                printMap();
                cmd = getch();
                switch(cmd){
                    case 'h':
                    case 'j':
                    case 'k':
                    case 'l':
                        move(cmd);
                        screen_clear();
                        break;
                    case 'd':
                        displayHelp();
                        cmd = getch();
                        screen_clear();
                        break;
                    case 'n':
                    //��������� �ð���� ���� �� ù��° �ʺ��� �ٽý���
                        break;
                    case 'e':
                    //���� ���� ���Ͽ� �����ϰ� ����
                        end = clock();
                        t1 = (float) ((end - start) /  CLOCKS_PER_SEC);
                        exit(0);
                    case 't':
                        break;
            }
        }
                    end = clock();
                    t1 = (float) ((end - start) / CLOCKS_PER_SEC);
    }
    }
}

void move(char dir){
    map[Py][Px] = ' ';
    switch(dir){
        case 'h':
            Px = Px - 1;
            if(map[Py][Px] == '#')
                Px = Px + 1;
            if(map[Py][Px] == '$'){
                for(int i=0; i<gold_count; i++){
                    if((gold_x[i] == Px) && (gold_y[i] == Py)){
                        gold_x[i] = gold_x[i] - 1;
                        if((map[gold_y[i]][gold_x[i]] == '#') ||
                           (map[gold_y[i]][gold_x[i]] == '$')){
                            gold_x[i] = gold_x[i] + 1;
                            Px = Px + 1;
                        }
                    }
                }
            }
            break;
        case 'j':
            Py = Py + 1;
            if(map[Py][Px] == '#')
                Py = Py - 1;
            if(map[Py][Px] == '$'){
                for(int i=0; i<gold_count; i++){
                    if((gold_x[i] == Px) && (gold_y[i] == Py)){
                        gold_y[i] = gold_y[i] + 1;
                        if((map[gold_y[i]][gold_x[i]] == '#') ||
                           (map[gold_y[i]][gold_x[i]] == '$')){
                            gold_y[i] = gold_y[i] - 1;
                            Py = Py - 1;
                        }
                    }
                }
            }
            break;
        case 'k':
            Py = Py - 1;
            if(map[Py][Px] == '#')
                Py = Py + 1;
             if(map[Py][Px] == '$'){
                for(int i=0; i<gold_count; i++){
                    if((gold_x[i] == Px) && (gold_y[i] == Py)){
                        gold_y[i] = gold_y[i] - 1;
                        if((map[gold_y[i]][gold_x[i]] == '#') ||
                           (map[gold_y[i]][gold_x[i]] == '$')){
                            gold_y[i] = gold_y[i] + 1;
                            Py = Py + 1;
                        }
                    }
                }
            }
            break;
        case 'l':
            Px = Px + 1;
            if(map[Py][Px] == '#')
                Px = Px - 1;
            if(map[Py][Px] == '$'){
                for(int i=0; i<gold_count; i++){
                    if((gold_x[i] == Px) && (gold_y[i] == Py)){
                        gold_x[i] = gold_x[i] + 1;
                        if((map[gold_y[i]][gold_x[i]] == '#') ||
                           (map[gold_y[i]][gold_x[i]] == '$')){
                            gold_x[i] = gold_x[i] - 1;
                            Px = Px - 1;
                        }
                    }
                }
            }
            break;
    }
}
void screen_clear(){
    system("clear");
    printf("Hello %s\n\n",user_name);
}

void displayHelp(){
    printf("h(����), j(�Ʒ�), k(��), l(������)\n");
    printf("u(undo)\n");
    printf("r(replay)\n");
    printf("n(new)\n");
    printf("e(exit)\n");
    printf("s(save)\n");
    printf("f(file load)\n");
    printf("d(display help)\n");
    printf("t(top)\n");
}

void readMap(int level){
    FILE* map_file;
    int map_level = 0;
    int row=0, col=0;
    int temp_col;
    char temp_char;
    int count = 0;

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

            if(map[i][j] == '@'){ // �ʱ� �÷��̾� ��ġ ����
                Px = j;
                Py = i;
            }else if(map[i][j] == '#'){
                wall_x[wall_count] = j;
                wall_y[wall_count] = i;
                wall_count++;
            }else if(map[i][j] == 'O'){
                slot_x[slot_count] = j;
                slot_y[slot_count] = i;
                slot_count++;
            }else if(map[i][j] == '$'){
                gold_x[gold_count] = j;
                gold_y[gold_count] = i;
                gold_count++;
            }


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
            if(map[i][j] == '\n' && count ==0){ //��ܿ� map���� ���о������
                count++;
                map[i][j] = fgetc(map_file);
            }
            if(map[i][j] == '\n'){
                for(; j<map_cols-1; j++)
                    map[i][j] = ' ';

                if(map[i][j] == ' ' || map[i][j] == '\n')
                    map[i][j] = '\n';
            }
        }
    }
    if(gold_count != slot_count){
        printf("$�� 0�� ������ �����ʾ� �����մϴ�.\n");
        exit(1);
    }
    fclose(map_file);
}

void printMap(){
    map[Py][Px] = '@';

    for(int k=0; k<slot_count; k++){
        if(map[slot_y[k]][slot_x[k]] == ' ')
            map[slot_y[k]][slot_x[k]] = 'O';
    }
    for(int k=0; k<gold_count; k++){
        map[gold_y[k]][gold_x[k]] = '$';
    }
    for(int i=0; i<map_rows; i++){
        for(int j=0; j<map_cols; j++){
            putchar(map[i][j]);
        }
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