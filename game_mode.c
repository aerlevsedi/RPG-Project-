#include <ncurses.h>
#include "game_mode.h"
#include "instruction_mode.h"
#include "attack_mode.h"
#define NL printw("\n")

int board[8][8]={
    {2,2,2,2,2,2,2,2},
    {2,9,1,9,1,1,3,2},
    {2,1,1,1,1,1,1,2},
    {2,1,7,1,2,1,9,2},
    {2,1,1,1,2,1,1,2},
    {2,1,1,1,2,2,1,2},
    {2,1,1,1,1,1,1,2},
    {2,2,2,2,2,2,2,2}
};

void write_board()
{
    clear();
    start_color();
    init_pair( 7, COLOR_RED, COLOR_BLACK );
    init_pair( 1, COLOR_WHITE, COLOR_BLACK );
    init_pair( 2, COLOR_GREEN, COLOR_BLACK );
    init_pair( 3, COLOR_BLUE, COLOR_BLACK );
    init_pair( 9, COLOR_YELLOW, COLOR_BLACK );

    printw("Your lifes: %d, || Enemies to kill: %d/%d, || Bag's volume: %d/%d\n\n", lifes, enemies, enemies_total, bag_hero, bag_max);
    for(int i=0; i<=7; i++){
        for(int j=0; j<=7; j++){
            attron( COLOR_PAIR( board[i][j]));
            printw("%d", board[i][j]);
            attroff( COLOR_PAIR( board[i][j]));
        }
        NL;
    }
    NL;
    attron( A_REVERSE );
    printw("I - Instruction || B - Bag || Escape - Exit\n");
    attroff( A_REVERSE);
}

typedef struct near_enemies{
    int x, y;
} Enem;

Enem list_enemies[9];

typedef struct counter_enemies{
    int number, hp;
} CountEnemies;

CountEnemies find_enemy(int h_x, int h_y)
{
    struct near_enemies ne;
    ne.x=h_x; ne.y=h_y;
    struct counter_enemies count_enem;
    count_enem.number=0; count_enem.hp=0;

    for(int i=0; i<=8; i++){    //clears list of enemies
        list_enemies[i].x=-1;
        list_enemies[i].y=-1;
    }

    for(int j=-1; j<=1; j++){   /* up */
        if(board[h_y-1][h_x+j]%3==0){
            count_enem.number++;
            count_enem.hp+=board[h_y-1][h_x+j];
            ne.x=h_x+j;
            ne.y=h_y-1;
            list_enemies[count_enem.number]=ne;
        }
    }

    if(board[h_y][h_x-1]%3==0){ /* left */
        count_enem.number++;
        count_enem.hp+=board[h_y][h_x-1];
        ne.x=h_x-1;
        ne.y=h_y;
        list_enemies[count_enem.number]=ne;
    }
    if(board[h_y][h_x+1]%3==0){ /* right */
        count_enem.number++;
        count_enem.hp+=board[h_y][h_x+1];
        ne.x=h_x+1;
        ne.y=h_y;
        list_enemies[count_enem.number]=ne;
    }

    for(int j=-1; j<=1; j++){ /* down */
        if(board[h_y+1][h_x+j]%3==0){
            count_enem.number++;
            count_enem.hp+=board[h_y+1][h_x+j];
            ne.x=h_x+j;
            ne.y=h_y+1;
            list_enemies[count_enem.number]=ne;
        }
    }

    return count_enem;
}

int hero_x=2, hero_y=3, width, height, lifes, enemies, enemies_total, bag_hero, bag_max;

void what_effect()
{
    struct counter_enemies cur_count=find_enemy(hero_x, hero_y);
    if(cur_count.number>0){
        printw("\nCOUNTER=%d\n", cur_count.number);
        getch();
        if(start_attack(cur_count.hp)==1){ //if hero win delete enemies
            for(int i=1; i<=cur_count.number; i++){
                board[list_enemies[i].y][list_enemies[i].x]=1;
            }
            enemies-=cur_count.number;
            if(enemies==0){
                /* GAME OVER */
                clear();
                printw("YOU WON!\n\nPress Escape to leave.\n");
                while(1){
                    char step=getch();
                    if(step==27) break;
                }
            }
        }else{
            lifes--;
            if(lifes==0){
                /* GAME OVER */
                clear();
                printw("YOU LOST!\n\nPress Escape to leave.\n");
                while(1){
                    char step=getch();
                    if(step==27) break;
                }
            }
        }
    }
}

void start_game()
{
    clear();

    char step;
    width=8; height=8;
    lifes=7;
    enemies=4; enemies_total=4;
    bag_hero=3; bag_max=10;

    write_board();

    while(1){
        step=getch();
        if(step==2){    /* down */
            if(board[hero_y+1][hero_x]==1){ /* checks if free and changing address */
                board[hero_y][hero_x]=1;
                board[hero_y+1][hero_x]=7;
                hero_y=hero_y+1;

                what_effect();
            }
            write_board();
        }else if(step==3){  /* up */
            if(board[hero_y-1][hero_x]==1){
                board[hero_y][hero_x]=1;
                board[hero_y-1][hero_x]=7;
                hero_y=hero_y-1;

                what_effect();
            }
            write_board();
        }else if(step==4){  /* left */
            if(board[hero_y][hero_x-1]==1){
                board[hero_y][hero_x]=1;
                board[hero_y][hero_x-1]=7;
                hero_x=hero_x-1;

                what_effect();
            }
            write_board();
        }else if(step==5){  /* right */
            if(board[hero_y][hero_x+1]==1){
                board[hero_y][hero_x]=1;
                board[hero_y][hero_x+1]=7;
                hero_x=hero_x+1;

                what_effect();
            }
            write_board();
        }else if(step==27){ /* escape */
            break;
        }else if(step==73){
            write_instruction();
            write_board();
        }else{
            printw("No such instruction.");
            write_board();
        }
    }
}
