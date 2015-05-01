#ifndef TETROMINO_H
#define TETROMINO_H

#include "grid.h"
// enums for tetrominos

enum Block_Type
{
	LONG_BLOCK,
	L_BLOCK,
	T_BLOCK,
	RL_BLOCK,
	S_BLOCK,
	Z_BLOCK,
	SQUARE_BLOCK,
	BLOCK_TYPE_TOTAL
};

enum angle {NO_TURNS, ONE_TURN, TWO_TURNS, THREE_TURNS};
//           0         1         2          3

#define ACTIVE   1
#define INACTIVE 0

// object typedefs
typedef struct{
	int active;
	int shape;
	int orientation;
	//block positions
	int pivot_x;
	int pivot_y;
	int rot1_x;
	int rot1_y;
	int rot2_x;
	int rot2_y;
	int rot3_x;
	int rot3_y;
} tetromino;  //these are the piees that fall

// function prototypes

// random for new tetromino
void set_rand();
int  get_type();

// creation and activation
tetromino *tetromino_new(int);
void tetromino_mod(tetromino*);
void tetromino_activate(tetromino*);

//  movement
void tetromino_rotate(tetromino*, int*);
void tetromino_shift_right(tetromino*, int*);
void tetromino_shift_left(tetromino*, int*);
void tetromino_drop(tetromino*, int*);

// grid interation
int tetromino_lock(tetromino*, int*);
void tetromino_into_grid(tetromino*, int*);

#endif