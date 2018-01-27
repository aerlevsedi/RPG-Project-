#include <ncurses.h>
#include "game_mode.h"
#include "instruction_mode.h"
#define NL printw("\n")

int enemies_hp, difficulty;

void write_screen()
{
    clear();

    start_color();
    init_pair( 7, COLOR_RED, COLOR_BLACK );

    int hero_hp=10;

    printw("Your lifes: %d, || Enemies to kill: %d/%d, || Bag's volume: %d/%d\n\n", lifes, enemies, enemies_total, bag_hero, bag_max);
    attron( COLOR_PAIR(7) );
    printw("Your HP: %d, || Enemies' HP: %d", hero_hp, enemies_hp);
    attroff( COLOR_PAIR(7) );
    NL;

    /*
    user can choose between three action:
    -knifes
    -arch
    -sword
    -fist
    each has some value and can hit enemies with such power and take away their hp
    enemies will get random value of their hit depending on the difficult level choosed by user
    (this value can be count as random from 1 to number of level or etc)

    after each hit on the screan will apear some information about disease and the counters of hp will change
    */
}

int start_attack(int x, int y)
{
    char step;
    enemies_hp=x;
    difficulty=y;
    write_screen();
    while(1){   /* it should start a fight and after its finished return result of it and come back to map */
        step=getch();

        write_screen();
        if(step==27){
            break;
        }else{
            write_screen();
        }
    }

    return 1;
}




