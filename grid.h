#ifndef GRID_H
#define GRID_H

// game parameters

#define MAXROW 19
#define MAXCOL 11
#define CELLS  MAXROW*MAXCOL

// what the grid is filled with

#define FULL  1
#define EMPTY 0

// functions
// offsets
int grid_coords_2_offset(int, int); // x,y
int grid_offset_2_x(int); // verified
int grid_offset_2_y(int); // verified

// init
//void init_grid(int*);

// grid manipulation
int  grid_get(int*, int, int); // x,y ?? just index ??
void grid_set(int*, int, int , int); // set x,y to b //
void grid_swap_cells(int*, int, int, int); // swap values r1,c with r2,c // confirmed

// operations based on rows

int  grid_row_full(int*, int); // is row r full in grid
int  grid_row_any(int*, int);  // any high in row r
void grid_row_clear(int*, int); // clear row r
void grid_row_swap(int*, int, int); // swap rows r1 and r2 via grid_swaps

#endif