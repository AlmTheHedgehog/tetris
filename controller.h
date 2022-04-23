#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "structs.h"
#define BUT_DELEY 200

void exit_check(short int *cur_screen);
void main_events_check(short int *cur_screen, short int* game_field);
short int butt_collision(short int* game_field, short int cur_piece_kind, short int cur_piece_rot, short int piece_left_top_bt_right[4]);
short int center_of_from_left(short int cur_piece_kind, short int cur_piece_rot);
void put_piece_on_place(short int* game_field, short int cur_piece_kind, short int cur_piece_rot, short int piece_left_top_bt_right[4]);
void length_of_piece(short int piece_left_top_bt_right[4], short int cur_piece_kind, short int cur_piece_rot);

#endif