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
    static short int cur_piece_kind = 0, cur_piece_rot = 0, piece_left_top_bt_right[4] = {(FIELD_WIDTH / 2) - 1, 0, 1, 1},
                     animation_del = 0, move_dir = 0;
    main_draw(game_field, piece_left_top_bt_right, cur_piece_kind, cur_piece_rot);
    if(animation_del >= DELEY_BTW_ANIM){   
        animation_del = 0;
        if(butt_collision(game_field, cur_piece_kind, cur_piece_rot, piece_left_top_bt_right)){
            //reset falling piece
            cur_piece_kind = rand() % 7;
            piece_left_top_bt_right[0] = (FIELD_WIDTH / 2) - center_of_from_left(cur_piece_kind, cur_piece_rot);
            piece_left_top_bt_right[1] = 0;
            cur_piece_rot = 0;
            move_dir = 0;
            length_of_piece(piece_left_top_bt_right, cur_piece_kind, cur_piece_rot);//measure height and length of piece
        }else{
            piece_left_top_bt_right[1]++;
            if(move_dir == 1){
                if((piece_left_top_bt_right[0] > 0) && (1)){              //+collision with left with field
                    piece_left_top_bt_right[0]--;
                }
            }else if(move_dir == 2){
                if(((piece_left_top_bt_right[0] + piece_left_top_bt_right[3]) < (FIELD_WIDTH - 1)) && (1)){ //+collision with right with field
                    piece_left_top_bt_right[0]++;
                }
            }
            move_dir = 0;
        }
    }else{
        animation_del++;
    }
    if(gfx_isKeyDown(SDLK_LEFT)){
        if((move_dir == 0) && (animation_del > ((DELEY_BTW_ANIM/4)*3))){
            move_dir = 1;
        }
    }else if(gfx_isKeyDown(SDLK_RIGHT)){
        if((move_dir == 0) && (animation_del > ((DELEY_BTW_ANIM/4)*3))){
            move_dir = 2;
        }
    }
    if(gfx_isKeyDown(SDLK_DOWN)){

    }
    //check if full row
}

short int butt_collision(short int* game_field, short int cur_piece_kind, short int cur_piece_rot,
                            short int piece_left_top_bt_right[4]){
    if((piece_left_top_bt_right[2] + piece_left_top_bt_right[1]) == (FIELD_HEIGHT - 1)){
        put_piece_on_place(game_field, cur_piece_kind, cur_piece_rot, piece_left_top_bt_right);
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

void length_of_piece(short int piece_left_top_bt_right[4], short int cur_piece_kind, short int cur_piece_rot){
    short int max_height[4] = {3, 3, 3, 3}, max_length[4] = {3, 3, 3, 3};
    for(int i = 0; i < 4; i++){
        while((max_length[i] > 0) && (pieces[cur_piece_kind][cur_piece_rot][i][max_length[i]] == 0)){
            max_length[i]--;
        }
    }
    for(int i = 0; i < 4; i++){
        while((max_height[i] > 0) && (pieces[cur_piece_kind][cur_piece_rot][max_height[i]][i] == 0)){
            max_height[i]--;
        }
    }
    piece_left_top_bt_right[2] = max_height[0];
    piece_left_top_bt_right[3] = max_length[0];
    for(int i = 1; i < 4; i++){
        if(max_height[i] > piece_left_top_bt_right[2]){
            piece_left_top_bt_right[2] = max_height[i];
        }
        if(max_length[i] > piece_left_top_bt_right[3]){
            piece_left_top_bt_right[3] = max_length[i];
        }
    }
}

void put_piece_on_place(short int* game_field, short int cur_piece_kind, short int cur_piece_rot, 
                        short int piece_left_top_bt_right[4]){
    for(int wdt = 0; wdt < 4; wdt++){
        for(int hgt = 0; hgt < 4; hgt++){
            if(pieces[cur_piece_kind][cur_piece_rot][hgt][wdt] > 0){
                *(game_field + (wdt + piece_left_top_bt_right[0])*FIELD_HEIGHT + (hgt + piece_left_top_bt_right[1])) = 1;
            }
        }
    }
}

