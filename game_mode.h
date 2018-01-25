#ifndef GAME_MODE_H_INCLUDED
#define GAME_MODE_H_INCLUDED

int board[8][8];
int hero_x, hero_y, width, height, lifes, enemies, enemies_total, bag_hero, bag_max;
typedef struct near_enemies Enem;   /* struct for enemy with x- and y-attributs */
typedef struct counter_enemies CountEnemies;
CountEnemies find_enemy(int h_x, int h_y);   /* finds enemies that are near to the hero and returns number of them */
void start_game();  /* function with main game mode with moving on the map etc */
void write_board(); /* write on the screen the map and bunch of infos */
void what_effect(); /* checks if hero is under attack */
#endif // GAME_MODE_H_INCLUDED
