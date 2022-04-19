#include <stdlib.h>
#include "primlib.h"
#include "controller.h"
#include "graphics.h"
#include "structs.h"

#if (SCR_WIDTH / FIELD_WIDTH) < (SCR_HEIGHT/FIELD_HEIGHT)
    const short int CELL_SIZE = SCR_WIDTH / FIELD_WIDTH;
    const short int FIELD_LEFT_TOP[2] = {0, (SCR_HEIGHT/2)-((CELL_SIZE*FIELD_HEIGHT)/2) - 1};
#else 
    const short int CELL_SIZE = SCR_HEIGHT/FIELD_HEIGHT;
    const short int FIELD_LEFT_TOP[2] = {(SCR_WIDTH/2)-((CELL_SIZE*FIELD_WIDTH)/2) - 1, 0};
#endif

void init_matrix(short int* game_field){
    for(int i = 0; i < FIELD_WIDTH; i++){
        for(int j = 0; j < FIELD_HEIGHT; j++){
            *(game_field + i*FIELD_HEIGHT + j) = 0;
        }
    }
}