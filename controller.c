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
                     animation_del = 0, move_dir = 0, but_del_check = 0;
    main_draw(game_field, piece_left_top_bt_right, cur_piece_kind, cur_piece_rot);
    if(animation_del >= DELEY_BTW_ANIM){   
        animation_del = 0;
        if(butt_collision(game_field, cur_piece_kind, cur_piece_rot, piece_left_top_bt_right)){
            put_piece_on_place(game_field, cur_piece_kind, cur_piece_rot, piece_left_top_bt_right);
            full_rows_check(game_field);
            vars_piece_reset(&cur_piece_kind, &cur_piece_rot, piece_left_top_bt_right, &move_dir, &but_del_check);
            if(field_collision(game_field, cur_piece_kind, cur_piece_rot, piece_left_top_bt_right)){
                main_draw(game_field, piece_left_top_bt_right, cur_piece_kind, cur_piece_rot);
                init_matrix(game_field, FIELD_WIDTH, FIELD_HEIGHT);
                *cur_screen = 1;
            }
        }else{
            piece_left_top_bt_right[1]++;
        }
    }else{
        animation_del++;
    }
    but_press_check(&move_dir, animation_del);
    if((move_dir != 0) && (*cur_screen == 0)){
        if(but_del_check == 0){
            move_events(game_field, cur_piece_kind, &cur_piece_rot, piece_left_top_bt_right, move_dir);
        }
        but_del_check++;
    }
    if(but_del_check >= BUT_DELEY/3){
        move_dir = 0;
        but_del_check = 0;
    }else if((*cur_screen == 0) && ((but_del_check >= (BUT_DELEY/4)) && ((((move_dir == 1) && (gfx_isKeyDown(SDLK_LEFT))) ||
            ((move_dir == 2) && (gfx_isKeyDown(SDLK_RIGHT)))) || ((move_dir == 4) && (gfx_isKeyDown(SDLK_r)))))){
        but_del_check = 1;
        move_events(game_field, cur_piece_kind, &cur_piece_rot, piece_left_top_bt_right, move_dir);
    }
}

void final_events_check(short int *cur_screen){
    final_draw();
    if(gfx_isKeyDown(SDLK_RETURN)){
        *cur_screen = 0;
    }
}

short int butt_collision(short int* game_field, short int cur_piece_kind, short int cur_piece_rot,
                            short int piece_left_top_bt_right[4]){
    piece_left_top_bt_right[1]++;
    if(field_collision(game_field, cur_piece_kind, cur_piece_rot, piece_left_top_bt_right)){
        piece_left_top_bt_right[1]--;
        return 1;
    }else{
        piece_left_top_bt_right[1]--;
    }
    if((piece_left_top_bt_right[2] + piece_left_top_bt_right[1]) == (FIELD_HEIGHT - 1)){
        return 1;
    }else{
        return 0;
    }
}
short int butt_collision_rr(short int* game_field, short int cur_piece_kind, short int cur_piece_rot,
                            short int piece_left_top_bt_right[4]){
    if(piece_left_top_bt_right[0] + piece_left_top_bt_right[3] > (FIELD_WIDTH - 1)){
        return 1;
    }
    if(piece_left_top_bt_right[0] < 0){
        return 1;
    }
    if(field_collision(game_field, cur_piece_kind, cur_piece_rot, piece_left_top_bt_right)){
        return 1;
    }else{
    }
    if((piece_left_top_bt_right[2] + piece_left_top_bt_right[1]) == (FIELD_HEIGHT - 1)){
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

void but_press_check(short int *move_dir, short int animation_del){
    //move_dir 0-none, 1-left, 2-right, 3-down, 4-rotate
    if(*move_dir == 0){
        if(gfx_isKeyDown(SDLK_LEFT)){
            *move_dir = 1;
        }else if(gfx_isKeyDown(SDLK_RIGHT)){
            *move_dir = 2;
        }else if(gfx_isKeyDown(SDLK_r)){
            *move_dir = 4;
        }
    }
    if(gfx_isKeyDown(SDLK_DOWN)){
        *move_dir = 3;
    }

}

void move_events(short int *game_field, short int cur_piece_kind, short int *cur_piece_rot,
        short int piece_left_top_bt_right[4], short int move_dir){
    if(move_dir == 1){
        piece_left_top_bt_right[0]--;
        if((piece_left_top_bt_right[0] < 0) ||
                (field_collision(game_field, cur_piece_kind, *cur_piece_rot, piece_left_top_bt_right))){
            piece_left_top_bt_right[0]++;   
        }
    }else if(move_dir == 2){
        piece_left_top_bt_right[0]++;
        if(((piece_left_top_bt_right[0] + piece_left_top_bt_right[3]) > (FIELD_WIDTH - 1)) || 
                (field_collision(game_field, cur_piece_kind, *cur_piece_rot, piece_left_top_bt_right))){
            piece_left_top_bt_right[0]--;
        }
    }else if(move_dir == 3){
        while(!butt_collision(game_field, cur_piece_kind, *cur_piece_rot, piece_left_top_bt_right)){
            piece_left_top_bt_right[1]++;
            main_draw(game_field, piece_left_top_bt_right, cur_piece_kind, *cur_piece_rot);
            SDL_Delay(11);
        }
        SDL_Delay(BUT_DELEY/7);
    }else if(move_dir == 4){
        move_rotation(game_field, cur_piece_kind, cur_piece_rot, piece_left_top_bt_right);
    }
}

void move_rotation(short int *game_field, short int cur_piece_kind, short int *cur_piece_rot, short int piece_left_top_bt_right[4]){
    short int prev_rot = *cur_piece_rot, coords_a_prev[2], coords_a_new[2];
    if(*cur_piece_rot >= 3){
        *cur_piece_rot = 0;
    }else{
        (*cur_piece_rot)++;
    }
    find_axe(cur_piece_kind, prev_rot, coords_a_prev);
    find_axe(cur_piece_kind, *cur_piece_rot, coords_a_new);
    piece_left_top_bt_right[0] += coords_a_prev[0] - coords_a_new[0];
    piece_left_top_bt_right[1] += coords_a_prev[1] - coords_a_new[1];
    length_of_piece(piece_left_top_bt_right, cur_piece_kind, *cur_piece_rot);
    if(butt_collision_rr(game_field, cur_piece_kind, *cur_piece_rot, piece_left_top_bt_right)){
        *cur_piece_rot = prev_rot;
        piece_left_top_bt_right[0] -= coords_a_prev[0] - coords_a_new[0];
        piece_left_top_bt_right[1] -= coords_a_prev[1] - coords_a_new[1];
        length_of_piece(piece_left_top_bt_right, cur_piece_kind, *cur_piece_rot);
    }
}

short int field_collision(short int* game_field, short int cur_piece_kind, short int cur_piece_rot, 
                        short int piece_left_top_bt_right[4]){
    char piece_cell_val = 0;
    for(int wdt = 0; wdt <= piece_left_top_bt_right[3]; wdt++){
        for(int hgt = 0; hgt <= piece_left_top_bt_right[2]; hgt++){
            piece_cell_val = pieces[cur_piece_kind][cur_piece_rot][hgt][wdt];
            if(piece_cell_val == 2){
                piece_cell_val = 1;
            }
            if((*(game_field + (wdt + piece_left_top_bt_right[0])*FIELD_HEIGHT + (hgt + piece_left_top_bt_right[1]))
                    + piece_cell_val) > 1){
                return 1;
            }
        }
    }
    return 0;
}

void full_rows_check(short int *game_field){
    short int row_sum;
    for(int row = 0; row < FIELD_HEIGHT; row++){
        row_sum = 0;
        for(int col = 0; col < FIELD_WIDTH; col++){
            row_sum += *(game_field + col*FIELD_HEIGHT + row);
        }
        if(row_sum == FIELD_WIDTH){
            short int sw_row = row, empty_sum = 1;
            while((sw_row > 0) && (empty_sum > 0)){
                empty_sum = 0;
                for(int col = 0; col < FIELD_WIDTH; col++){
                    *(game_field + col*FIELD_HEIGHT + sw_row) = *(game_field + col*FIELD_HEIGHT + (sw_row-1));
                    empty_sum += *(game_field + col*FIELD_HEIGHT + (sw_row-1));
                }
                sw_row--;
            }
            if(sw_row == 0){
                for(int col = 0; col < FIELD_WIDTH; col++){
                    *(game_field + col * FIELD_HEIGHT + sw_row) = 0;
                }
            }
        }
    }
}

void vars_piece_reset(short int *cur_piece_kind, short int *cur_piece_rot, short int piece_left_top_bt_right[4], short int *move_dir, 
                                                                                                        short int *but_del_check){
    *cur_piece_kind = rand() % 7;
    piece_left_top_bt_right[0] = (FIELD_WIDTH / 2) - center_of_from_left(*cur_piece_kind, *cur_piece_rot);
    piece_left_top_bt_right[1] = 0;
    *cur_piece_rot = 0;
    *move_dir = 0;
    *but_del_check = 0;
    length_of_piece(piece_left_top_bt_right, *cur_piece_kind, *cur_piece_rot);
}

void find_axe(short int cur_piece_kind, short int cur_piece_rot, short int coords[2]){
    for(int wdt = 0; wdt < 4; wdt++){
        for(int hgt = 0; hgt < 4; hgt++){
            if(pieces[cur_piece_kind][cur_piece_rot][hgt][wdt] == 2){
                coords[0] = wdt;
                coords[1] = hgt;
            }
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

