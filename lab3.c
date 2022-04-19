#include <stdlib.h>
#include "primlib.h"
#include "structs.h"
#include "controller.h"
#include "graphics.h"


int main(){
    if (gfx_init())
        exit(3);

    short int cur_screen = 0;

    while((cur_screen == 0) || (cur_screen == 1)){
        if(cur_screen == 0){

        }else{
        }
        exit_check(&cur_screen);
    }

    return 0;
}