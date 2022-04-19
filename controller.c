#include <stdlib.h>
#include "primlib.h"
#include "structs.h"
#include "graphics.h"
#include "controller.h"

void exit_check(short int* cur_screen){
    if(gfx_isKeyDown(SDLK_ESCAPE)){
        *cur_screen = 2;
    }
}
