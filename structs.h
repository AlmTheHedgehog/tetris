#ifndef STRUCT_H
#define STRUCT_H

//Game consts
#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10
//Graph consts
#define SCR_WIDTH 1280
#define SCR_HEIGHT 720
#define DELEY_BTW_FRAMES 500

const short int CELL_SIZE;
const short int FIELD_LEFT_TOP[2];
const char pieces[7 /*kind */ ][4 /* rotation */ ][4][4];

void init_matrix(short int* game_field);


#endif