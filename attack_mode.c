#include <ncurses.h>
#include "game_mode.h"
#include "instruction_mode.h"
#define NL printw("\n")

int enemies_hp;

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


}

int start_attack(int x)
{
    char step;
    enemies_hp=x;
    write_screen();
    while(1){
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




