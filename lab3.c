#include <stdlib.h>
#include <time.h>
#include "primlib.h"
#include "structs.h"
#include "controller.h"
#include "graphics.h"


int main(){
    if (gfx_init())
        exit(3);

    short int cur_screen = 0, game_field[FIELD_WIDTH][FIELD_HEIGHT], *game_field_ptr;//game_field(WIDTHxHEIGHT)
    game_field_ptr = &game_field[0][0];
    srand(time(NULL));
    init_matrix(game_field_ptr);
    while((cur_screen == 0) || (cur_screen == 1)){
        if(cur_screen == 0){
            main_events_check(&cur_screen, game_field_ptr);
        }else{
        }
        exit_check(&cur_screen);
    }

    return 0;
}