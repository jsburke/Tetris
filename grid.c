#include "grid.h"

int grid_coords_2_offset(int row, int col)
{
	return ((row * MAXCOL) + col);
}

int grid_offset_2_x(int offset)
{
	return (offset % MAXCOL);
}

int grid_offset_2_y(int offset)
{
	return (offset / MAXCOL);
}

/*// grid manipulation
void init_grid(int* game_grid)
{
	int index;
	for(index = 0; index < CELLS; index++)
	{
		game_grid[index] = EMPTY;
	}
}*/

int  grid_get(int* game_grid, int row, int col) // input as y val then x val
{
	int offset = grid_coords_2_offset(row, col);
	return game_grid[offset];
}

void grid_set(int* game_grid, int x, int y, int val)
{
	int offset = grid_coords_2_offset(y, x);
	game_grid[offset] = val;
}

void grid_swap_cells(int* game_grid, int row1, int row2, int col)
{
	int offset1, offset2, temp;
	offset1 = grid_coords_2_offset(row1, col);
	offset2 = grid_coords_2_offset(row2, col);

	temp = game_grid[offset1];
	game_grid[offset1] = game_grid[offset2];
	game_grid[offset2] = temp;

}

// operations based on rows

int  grid_row_full(int* game_grid, int row)
{
	int begin_row, end_row, index, res;
	begin_row = grid_coords_2_offset(row, 0);
	end_row   = grid_coords_2_offset(row, MAXCOL-1);

	res = 1; // assume row full
	
	for(index = begin_row; index <= end_row; index++){
		res = (game_grid[index] == EMPTY) ? 0:1;
		if(res == 0)
			break;
	}

	return res;
}

int  grid_row_any(int* game_grid, int row)
{
	int begin_row, end_row, index, res;
	begin_row = grid_coords_2_offset(row, 0);
	end_row   = grid_coords_2_offset(row, MAXCOL-1);

	res = 0; // assume the whole row is empty

	for(index = begin_row; index <= end_row; index++){
		res = (game_grid[index] == FULL) ? 1:0;
		if(res == 1)
			break;
	}	

	return res;
}

void grid_row_clear(int* game_grid, int row)
{
	int begin_row, end_row, index;
	begin_row = grid_coords_2_offset(row, 0);
	end_row   = grid_coords_2_offset(row, MAXCOL-1);

	for(index = begin_row; index <= end_row; index++){
		game_grid[index] = EMPTY;
	}
}

void grid_row_swap(int* game_grid, int row1, int row2)
{
	int col;
	
	for(col = 0; col < MAXCOL; col++){
		grid_swap_cells(game_grid, row1, row2, col);
	}
}
