#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_mode.h"
#include "instruction_mode.h"
#define NL printw("\n")

int enemies_hp, hero_hp, difficulty;

void write_battle(int line)
{
    clear();

    start_color();
    init_pair( 7, COLOR_RED, COLOR_BLACK );

    printw("Your lifes: %d, || Enemies to kill: %d/%d, || Bag's volume: %d/%d\n\n", lifes, enemies, enemies_total, bag_hero, bag_max);
    attron( COLOR_PAIR(7) );
    printw("Your HP: %d, || Enemies' HP: %d, dif=%d", hero_hp, enemies_hp);
    attroff( COLOR_PAIR(7) );
    NL;

    if(line==-1 || line==0){
        attron( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Knifes\n");
        attroff( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Arch\n");
        printw("Sword\n");
        printw("Fist\n");
    }else if(line==1){
        printw("Knifes\n");
        attron( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Arch\n");
        attroff( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Sword\n");
        printw("Fist\n");
    }else if(line==2){
        printw("Knifes\n");
        printw("Arch\n");
        attron( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Sword\n");
        attroff( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Fist\n");
    }else{
        printw("Knifes\n");
        printw("Arch\n");
        printw("Sword\n");
        attron( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Fist\n");
        attroff( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
    }

    /*
    user can choose between three action:
    -knifes -2
    -arch -3
    -sword -5
    -fist -1
    each has some value and can hit enemies with such power and take away their hp
    enemies will get random value of their hit depending on the difficult level choosed by user
    (this value can be count as random from 1 to number of level or etc)

    after each hit on the screan will apear some information about disease and the counters of hp will change
    */
}

int enemies_attack()
{
    int hit;
    hit=rand()%(4+difficulty);

    hero_hp-=hit;
    if(hero_hp<0) return 0;
    else return 1;

}

int start_attack(int x, int y)
{
    char znak;
    int line_number=0, result=0;
    enemies_hp=x;
    hero_hp=10;
    difficulty=y;
    write_battle(-1);
    while(1){   /* it should start a fight and after its finished return result of it and come back to map */
        znak=getch();

        while(znak!=10){
            if(znak==2){
                line_number++;
                if(line_number>=4) line_number=0;
            }else if(znak==3){
                line_number--;
                if(line_number<=-1) line_number=3;
            }
            write_battle(line_number);
            znak=getch();
        }

        if(line_number==0){
            enemies_hp-=2;
            if(enemies_hp<=0){
                result=1;
                break;
            }
        }else if(line_number==1){
            enemies_hp-=3;
            if(enemies_hp<=0){
                result=1;
                break;
            }
        }else if(line_number==2){
            enemies_hp-=5;
            if(enemies_hp<=0){
                result=1;
                break;
            }
        }else if(line_number==3){
            enemies_hp-=1;
            if(enemies_hp<=0){
                result=1;
                break;
            }
        }

        write_battle(line_number);

        if(enemies_attack()==0){
            result=0;
            break;
        }

        write_battle(line_number);
    }

    return result;
}




