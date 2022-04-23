#include <stdlib.h>
#include "primlib.h"
#include "structs.h"
#include "graphics.h"

void main_draw(short int* game_field, short int piece_left_top_bt_right[4], short int cur_piece_kind, short int cur_piece_rot){
    gfx_filledRect(0, 0, SCR_WIDTH - 1, SCR_HEIGHT - 1, BLACK);
    for(int wdt = 0; wdt < FIELD_WIDTH; wdt++){
        for(int hgt = 0; hgt < FIELD_HEIGHT; hgt++){
            if(*(game_field + wdt*FIELD_HEIGHT + hgt) == 1){
                draw_cell(wdt, hgt, 0);
            }
        }
    }
    draw_piece(piece_left_top_bt_right, cur_piece_kind, cur_piece_rot);
    draw_border();
    gfx_updateScreen();
    SDL_Delay(DELEY_BTW_FRAMES);
}

void final_draw(){
    gfx_filledRect(0, 0, SCR_WIDTH - 1, SCR_HEIGHT - 1, BLACK);
    gfx_textout((SCR_WIDTH/2)-(SCR_WIDTH/27), SCR_HEIGHT/2, "You lost =(", WHITE);
    gfx_textout((SCR_WIDTH/2)-(SCR_WIDTH/12), (SCR_HEIGHT/2)+(SCR_HEIGHT/27), "Press ENTER to play again!", WHITE);
    gfx_updateScreen();
    SDL_Delay(DELEY_BTW_FRAMES);
}

void draw_cell(short int width_lvl, short int height_lvl, short int is_axe){// add green color for the center 
    if(is_axe){
        gfx_filledRect(FIELD_LEFT_TOP[0]+(width_lvl*CELL_SIZE), FIELD_LEFT_TOP[1]+(height_lvl*CELL_SIZE),
            FIELD_LEFT_TOP[0]+((width_lvl+1)*CELL_SIZE), FIELD_LEFT_TOP[1]+((height_lvl+1)*CELL_SIZE), GREEN);
    }else{
        gfx_filledRect(FIELD_LEFT_TOP[0]+(width_lvl*CELL_SIZE), FIELD_LEFT_TOP[1]+(height_lvl*CELL_SIZE),
            FIELD_LEFT_TOP[0]+((width_lvl+1)*CELL_SIZE), FIELD_LEFT_TOP[1]+((height_lvl+1)*CELL_SIZE), YELLOW);
    }
}

void draw_border(){
    gfx_rect(FIELD_LEFT_TOP[0], FIELD_LEFT_TOP[1], FIELD_LEFT_TOP[0] + (CELL_SIZE * FIELD_WIDTH),
        FIELD_LEFT_TOP[1] + (CELL_SIZE * FIELD_HEIGHT), GREEN);
}

void draw_piece(short int piece_left_top_bt_right[4], short int cur_piece_kind, short int cur_piece_rot){
    for(int wdt = 0; wdt < 4; wdt++){
        for(int hgt = 0; hgt < 4; hgt++){
            if(pieces[cur_piece_kind][cur_piece_rot][hgt][wdt] == 1){
                draw_cell(wdt + piece_left_top_bt_right[0], hgt + piece_left_top_bt_right[1], 0);
            }else if(pieces[cur_piece_kind][cur_piece_rot][hgt][wdt] == 2){
                draw_cell(wdt + piece_left_top_bt_right[0], hgt + piece_left_top_bt_right[1], 1);
            }
        }
    }    
}