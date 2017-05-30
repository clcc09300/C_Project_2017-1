#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termio.h>

#define MAX_STAGE 5
#define MAX_RC 50

char map[MAX_RC][MAX_RC];
int map_rows;
int map_cols;

char user_name[10];
clock_t start, end;
float t1,t2,t3,t4,t5;

void readMap(int level);
void printMap();
void displayHelp();
int getch();
void screen_clear();
void top();

void main(){
    while(1){
        printf("input name : ");
        gets(user_name);
        user_name[10] = '\0';
        screen_clear();
        while(1){
            char command = getch();
            switch(command){
                case 'd':
                    displayHelp();
                    command = getch();
                    screen_clear();
                    break;
                case 'n':
                    //��������� �ð���� ���� �� ù��° �ʺ��� �ٽý���
                    break;
                case 'e':
                    //���� ���� ���Ͽ� �����ϰ� ����
                    exit(0);
                case 't':
                    top();
                default:
                    start = clock();
                    readMap(1);
                    printMap();
                    end = clock();
                    t1 = (float) ((end - start) / CLOCKS_PER_SEC);
                    command = getch();
                    screen_clear();
            }
        }
    }
}

void top(){
        int key= getch();
        switch(key)
        {
            char buf[10000];
            char buf_sec[2000];
            float sec;
            int map_num;

            case 1:
            fopen("ranking.txt","r");
            while(fscanf(fopen("ranking.txt","r"),"%s  %f%s",buf,sec,buf_sec )!="map 2")
             {
                 printf("%s  %f%s",buf,sec,buf_sec);
             }
            fclose(fopen("ranking.txt","r"));
            break;

            case 2:
            fopen("ranking.txt","r");
            while(fscanf(fopen("ranking.txt","r"),"%s  %f%s",buf,sec,buf_sec )!="map 3")
             {
                 printf("%s  %f%s",buf,sec,buf_sec);
             }
            fclose(fopen("ranking.txt","r"));
            break;

            case 3:
            fopen("ranking.txt","r");
            while(fscanf(fopen("ranking.txt","r"),"%s  %f%s",buf,sec,buf_sec )!="map 2")
             {
                 printf("%s  %f%s",buf,sec,buf_sec);
             }
            fclose(fopen("ranking.txt","r"));
            break;

            case 4:
            fopen("ranking.txt","r");
            while(fscanf(fopen("ranking.txt","r"),"%s  %f%s",buf,sec,buf_sec )!="map 2")
             {
                 printf("%s  %f%s",buf,sec,buf_sec);
             }
            fclose(fopen("ranking.txt","r"));
            break;

            case 5:
            fopen("ranking.txt","r");
            while(fscanf(fopen("ranking.txt","r"),"%s  %f%s",buf,sec,buf_sec )!="map 2")
             {
                 printf("%s  %f%s",buf,sec,buf_sec);
             }
            fclose(fopen("ranking.txt","r"));
            break;

            default :
            fopen("ranking.txt","r");
            while(ranking = fgetc(fopen("ranking.txt","r"))!=EOF)
            {
                putc(ranking,stdout);
            }
            fclose(fopen("ranking.txt","r"));
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