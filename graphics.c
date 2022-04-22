#include <stdlib.h>
#include "primlib.h"
#include "structs.h"
#include "graphics.h"

void main_draw_static(short int* game_field){
    gfx_filledRect(0, 0, SCR_WIDTH - 1, SCR_HEIGHT - 1, BLACK);
    
    for(int wdt = 0; wdt < FIELD_WIDTH; wdt++){
        for(int hgt = 0; hgt < FIELD_HEIGHT; hgt++){
            if(*(game_field + wdt*FIELD_HEIGHT + hgt) == 1){
                draw_cell(wdt, hgt, 0);
            }
        }
    }
    draw_border();
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

void draw_finish(){
    gfx_updateScreen();
    SDL_Delay(DELEY_BTW_FRAMES);
}

void draw_piece(short int piece_left_top_bt[3], short int cur_piece_kind, short int cur_piece_rot){
    for(int wdt = 0; wdt < 4; wdt++){
        for(int hgt = 0; hgt < 4; hgt++){
            if(pieces[cur_piece_kind][cur_piece_rot][hgt][wdt] == 1){
                draw_cell(wdt + piece_left_top_bt[0], hgt + piece_left_top_bt[1], 0);
            }else if(pieces[cur_piece_kind][cur_piece_rot][hgt][wdt] == 2){
                draw_cell(wdt + piece_left_top_bt[0], hgt + piece_left_top_bt[1], 1);
            }
        }
    }    
}