#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "structs.h"

void main_draw_static(short int* game_field);
void draw_cell(short int width_lvl, short int height_lvl, short int is_axe);
void draw_border();
void draw_finish();
void draw_piece(short int piece_left_top_bt[3], short int cur_piece_kind, short int cur_piece_rot);


#endif