#include <stdlib.h>
#include "primlib.h"
#include "structs.h"
#include "graphics.h"
#include "controller.h"

void exit_check(short int *cur_screen){
    if(gfx_isKeyDown(SDLK_ESCAPE)){
        *cur_screen = 2;
    }
}

void main_events_check(short int *cur_screen, short int* game_field){
    static short int cur_piece_kind = 0, cur_piece_rot = 0, piece_left_top_bt[3] = {(FIELD_WIDTH / 2) - 1, 0, 1};
    draw_piece(piece_left_top_bt, cur_piece_kind, cur_piece_rot);
    if(butt_collision(game_field, cur_piece_kind, cur_piece_rot, piece_left_top_bt)){
        //reset falling piece
        //new kind and rotation!!!!
        piece_left_top_bt[0] = (FIELD_WIDTH / 2) - center_of_from_left(cur_piece_kind, cur_piece_rot);
        piece_left_top_bt[1] = 0;
        //piece_left_top_bt = length of piece(height)
    }else{
        piece_left_top_bt[1]++;
    }
}

short int butt_collision(short int* game_field, short int cur_piece_kind, short int cur_piece_rot, short int piece_left_top_bt[3]){
    if((piece_left_top_bt[2] + piece_left_top_bt[1]) == (FIELD_HEIGHT - 1)){
        put_piece_on_place(game_field, cur_piece_kind, cur_piece_rot, piece_left_top_bt);
        return 1;
    }else{
        return 0;
    }
}

short int center_of_from_left(short int cur_piece_kind, short int cur_piece_rot){
    if(pieces[cur_piece_kind][cur_piece_rot][0][3] == 0){
        return 1;
    }else{
        return 2;
    }
}

void put_piece_on_place(short int* game_field, short int cur_piece_kind, short int cur_piece_rot, short int piece_left_top_bt[3]){
    for(int wdt = 0; wdt < 4; wdt++){
        for(int hgt = 0; hgt < 4; hgt++){
            if(pieces[cur_piece_kind][cur_piece_rot][hgt][wdt] > 0){
                *(game_field + (wdt + piece_left_top_bt[0])*FIELD_HEIGHT + (hgt + piece_left_top_bt[1])) = 1;
            }
        }
    }
}

