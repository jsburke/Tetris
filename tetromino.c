#include "tetromino.h"
#include <time.h>
#include <stdlib.h>

//------------------------
// defs for in here only

void long_rotate(tetromino*, int*);
void l_rotate(tetromino*, int*);
void t_rotate(tetromino*, int*);
void rl_rotate(tetromino*, int*);
void s_rotate(tetromino*, int*);
void z_rotate(tetromino*, int*);


// random for new tetromino
void set_rand()
{
	srand(time(NULL));
}

int get_type()
{
	return rand() % BLOCK_TYPE_TOTAL;
}

// creation and activation
tetromino *tetromino_new(int active_in)
{
	tetromino* res;
	int        new_type, new_x, new_y;

	res = (tetromino*) malloc(sizeof(tetromino));

	new_type = get_type();

	res->active = active_in;
	res->shape  = new_type;

	res->orientation = 0;

	switch(new_type)
	{
		case LONG_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 1;
			
			res->pivot_x = new_x;
			res->pivot_y = new_y;
			
			res->rot1_x  = new_x;
			res->rot1_y  = new_y - 1;
			
			res->rot2_x  = new_x;
			res->rot2_y  = new_y + 1;
			
			res->rot3_x  = new_x;
			res->rot3_y  = new_y + 2;			
		break;

		case L_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 2;
			
			res->pivot_x = new_x;
			res->pivot_y = new_y;
			
			res->rot1_x  = new_x;
			res->rot1_y  = new_y - 2;
			
			res->rot2_x  = new_x;
			res->rot2_y  = new_y - 1;
			
			res->rot3_x  = new_x + 1;
			res->rot3_y  = new_y;			
		break;

		case T_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 0;
			
			res->pivot_x = new_x;
			res->pivot_y = new_y;
			
			res->rot1_x  = new_x - 1;
			res->rot1_y  = new_y;
			
			res->rot2_x  = new_x + 1;
			res->rot2_y  = new_y;
			
			res->rot3_x  = new_x;
			res->rot3_y  = new_y + 1;			
		break;

		case RL_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 2;
			
			res->pivot_x = new_x;
			res->pivot_y = new_y;
			
			res->rot1_x  = new_x;
			res->rot1_y  = new_y - 2;
			
			res->rot2_x  = new_x;
			res->rot2_y  = new_y - 1;
			
			res->rot3_x  = new_x - 1;
			res->rot3_y  = new_y;			
		break;

		case S_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 0;
			
			res->pivot_x = new_x;
			res->pivot_y = new_y;
			
			res->rot1_x  = new_x + 1;
			res->rot1_y  = new_y;
			
			res->rot2_x  = new_x;
			res->rot2_y  = new_y + 1;
			
			res->rot3_x  = new_x - 1;
			res->rot3_y  = new_y + 1;			
		break;


		case Z_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 0;
			
			res->pivot_x = new_x;
			res->pivot_y = new_y;
			
			res->rot1_x  = new_x - 1;
			res->rot1_y  = new_y;
			
			res->rot2_x  = new_x;
			res->rot2_y  = new_y + 1;
			
			res->rot3_x  = new_x + 1;
			res->rot3_y  = new_y + 1;			
		break;


		case SQUARE_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 0;
			
			res->pivot_x = new_x;
			res->pivot_y = new_y;
			
			res->rot1_x  = new_x + 1;
			res->rot1_y  = new_y;
			
			res->rot2_x  = new_x;
			res->rot2_y  = new_y + 1;
			
			res->rot3_x  = new_x + 1;
			res->rot3_y  = new_y + 1;			
		break;
	}

	return res;	
}

void tetromino_mod(tetromino* cur)
{
	int new_type, new_x, new_y;

	new_type = get_type();

	cur->active = INACTIVE;
	cur->shape  = new_type;
	cur->orientation = 0;

	switch(new_type)
	{
		case LONG_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 1;
			
			cur->pivot_x = new_x;
			cur->pivot_y = new_y;
			
			cur->rot1_x  = new_x;
			cur->rot1_y  = new_y - 1;
			
			cur->rot2_x  = new_x;
			cur->rot2_y  = new_y + 1;
			
			cur->rot3_x  = new_x;
			cur->rot3_y  = new_y + 2;			
		break;

		case L_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 2;
			
			cur->pivot_x = new_x;
			cur->pivot_y = new_y;
			
			cur->rot1_x  = new_x;
			cur->rot1_y  = new_y - 2;
			
			cur->rot2_x  = new_x;
			cur->rot2_y  = new_y - 1;
			
			cur->rot3_x  = new_x + 1;
			cur->rot3_y  = new_y;			
		break;

		case T_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 0;
			
			cur->pivot_x = new_x;
			cur->pivot_y = new_y;

			cur->rot1_x  = new_x - 1;
			cur->rot1_y  = new_y;
			
			cur->rot2_x  = new_x + 1;
			cur->rot2_y  = new_y;
			
			cur->rot3_x  = new_x;
			cur->rot3_y  = new_y + 1;			
		break;

		case RL_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 2;
			
			cur->pivot_x = new_x;
			cur->pivot_y = new_y;
			
			cur->rot1_x  = new_x;
			cur->rot1_y  = new_y - 2;
			
			cur->rot2_x  = new_x;
			cur->rot2_y  = new_y - 1;
			
			cur->rot3_x  = new_x - 1;
			cur->rot3_y  = new_y;			
		break;

		case S_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 0;
			
			cur->pivot_x = new_x;
			cur->pivot_y = new_y;
			
			cur->rot1_x  = new_x + 1;
			cur->rot1_y  = new_y;
			
			cur->rot2_x  = new_x;
			cur->rot2_y  = new_y + 1;
			
			cur->rot3_x  = new_x - 1;
			cur->rot3_y  = new_y + 1;			
		break;


		case Z_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 0;
			
			cur->pivot_x = new_x;
			cur->pivot_y = new_y;
			
			cur->rot1_x  = new_x - 1;
			cur->rot1_y  = new_y;
			
			cur->rot2_x  = new_x;
			cur->rot2_y  = new_y + 1;
			
			cur->rot3_x  = new_x + 1;
			cur->rot3_y  = new_y + 1;			
		break;


		case SQUARE_BLOCK:
			new_x = MAXCOL / 2;
			new_y = 0;
			
			cur->pivot_x = new_x;
			cur->pivot_y = new_y;
			
			cur->rot1_x  = new_x + 1;
			cur->rot1_y  = new_y;
			
			cur->rot2_x  = new_x;
			cur->rot2_y  = new_y + 1;
			
			cur->rot3_x  = new_x + 1;
			cur->rot3_y  = new_y + 1;			
		break;
	}

}

void tetromino_activate(tetromino* cur)
{
	cur->active = ACTIVE;
}

//  movement
void tetromino_rotate(tetromino* falling, int* grid)
{
	switch(falling->shape)
	{

		case SQUARE_BLOCK:
		//nothing to do...
		break;

		case LONG_BLOCK:
			long_rotate(falling, grid);
		break;

		case L_BLOCK:
			l_rotate(falling, grid);
		break;

		case T_BLOCK:
			t_rotate(falling, grid);
		break;

		case RL_BLOCK:
			rl_rotate(falling, grid);
		break;

		case S_BLOCK:
			s_rotate(falling, grid);
		break;

		case Z_BLOCK:
			z_rotate(falling, grid);
		break;
	}
}

void tetromino_shift_right(tetromino* falling, int* grid) //
{
	int check_x, check_y, check_1, check_2, check_3, check_4;

	check_1 = (grid_get(grid, falling->pivot_y, falling->pivot_x  + 1) == FULL) ? 0:1;
	check_2 = (grid_get(grid, falling->rot1_y, falling->rot1_x  + 1) == FULL) ? 0:1;
	check_3 = (grid_get(grid, falling->rot2_y, falling->rot2_x  + 1) == FULL) ? 0:1;
	check_4 = (grid_get(grid, falling->rot3_y, falling->rot3_x  + 1) == FULL) ? 0:1;

	if((check_1 == 1) && (check_2 == 1) && (check_3 == 1) && (check_4 == 1))
	{
		if((falling->pivot_x + 1 < MAXCOL) && (falling->rot1_x + 1 < MAXCOL) && (falling->rot2_x + 1 < MAXCOL) && (falling->rot3_x + 1 < MAXCOL))
		{
			falling->pivot_x += 1;
			falling->rot1_x += 1;
			falling->rot2_x += 1;
			falling->rot3_x += 1;
		}
	}

}

void tetromino_shift_left(tetromino* falling, int* grid) //
{
	int check_x, check_y, check_1, check_2, check_3, check_4;

	check_1 = (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL) ? 0:1;
	check_2 = (grid_get(grid, falling->rot1_y, falling->rot1_x - 1) == FULL) ? 0:1;
	check_3 = (grid_get(grid, falling->rot2_y, falling->rot2_x - 1) == FULL) ? 0:1;
	check_4 = (grid_get(grid, falling->rot3_y, falling->rot3_x - 1) == FULL) ? 0:1;

	if((check_1 == 1) && (check_2 == 1) && (check_3 == 1) && (check_4 == 1))
	{
		if((falling->pivot_x - 1 >= 0) && (falling->rot1_x - 1 >= 0) && (falling->rot2_x - 1 >= 0) && (falling->rot3_x - 1 >= 0))
		{
			falling->pivot_x -= 1;
			falling->rot1_x -= 1;
			falling->rot2_x -= 1;
			falling->rot3_x -= 1;
		}
	}

}

void tetromino_drop(tetromino* falling, int* grid) //
{
	int check_x, check_y, check_1, check_2, check_3, check_4;

	check_1 = (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL) ? 0:1;
	check_2 = (grid_get(grid, falling->rot1_y + 1, falling->rot1_x) == FULL) ? 0:1;
	check_3 = (grid_get(grid, falling->rot2_y + 1, falling->rot2_x) == FULL) ? 0:1;
	check_4 = (grid_get(grid, falling->rot3_y + 1, falling->rot3_x) == FULL) ? 0:1;

	if((check_1 == 1) && (check_2 == 1) && (check_3 == 1) && (check_4 == 1))
	{
		if((falling->pivot_y + 1 < MAXROW) && (falling->rot1_y + 1 < MAXROW) && (falling->rot2_y + 1 < MAXROW) && (falling->rot3_y + 1 < MAXROW))
		{
			falling->pivot_y += 1;
			falling->rot1_y += 1;
			falling->rot2_y += 1;
			falling->rot3_y += 1;
		}
	}

}

// grid interation
int tetromino_lock(tetromino* falling, int* grid)
{
	if((grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL))
		return 1;
	
	if((grid_get(grid, falling->rot1_y + 1, falling->rot1_x) == FULL))
		return 1;
	
	if((grid_get(grid, falling->rot2_y + 1, falling->rot2_x) == FULL))
		return 1;
	
	if((grid_get(grid, falling->rot3_y + 1, falling->rot3_x) == FULL))
		return 1;

	if(falling->pivot_y == MAXROW - 1)
		return 1;

	if(falling->rot1_y == MAXROW - 1)
		return 1;

	if(falling->rot2_y == MAXROW - 1)
		return 1;

	if(falling->rot3_y == MAXROW - 1)
		return 1;

	return 0;
}

void tetromino_into_grid(tetromino* falling, int* grid)
{
	grid_set(grid, falling->pivot_x, falling->pivot_y, FULL);
	grid_set(grid, falling->rot1_x, falling->rot1_y, FULL);
	grid_set(grid, falling->rot2_x, falling->rot2_y, FULL);
	grid_set(grid, falling->rot3_x, falling->rot3_y, FULL);
}

// c file only function

void long_rotate(tetromino* falling, int* grid)
{
	int check;

	check = 0;

	if(falling->orientation == NO_TURNS)
	{
		check += (falling->pivot_x + 1 >= MAXCOL)? 1:0; //rot1
		check += (grid_get(grid, falling-> pivot_y, falling->pivot_x + 1) == FULL)? 1:0;

		check += (falling->pivot_x - 1 < 0)? 1:0;  //rot2
		check += (grid_get(grid, falling-> pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		check += (falling->pivot_x - 2 < 0)? 1:0;  //rot3
		check += (grid_get(grid, falling-> pivot_y, falling->pivot_x - 2) == FULL)? 1:0;

		if(check == 0) //safe to modify
		{
			falling->orientation = ONE_TURN;

			falling->rot1_x = falling->pivot_x + 1;
			falling->rot1_y = falling->pivot_y;

			falling->rot2_x = falling->pivot_x - 1;
			falling->rot2_y = falling->pivot_y;

			falling->rot3_x = falling->pivot_x - 2;
			falling->rot3_y = falling->pivot_y;

		}
	}
	else // orientation is ONE_TURN
	{
		check += (falling->pivot_y - 1 < 0)? 1:0; //rot1
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;  //rot2
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_y + 2 >= MAXROW)? 1:0;  //rot3
		check += (grid_get(grid, falling->pivot_y + 2, falling->pivot_x) == FULL)? 1:0;

		if(check == 0) //safe to modify
		{
			falling->orientation = NO_TURNS;

			falling->rot1_x = falling->pivot_x;
			falling->rot1_y = falling->pivot_y - 1;

			falling->rot2_x = falling->pivot_x;
			falling->rot2_y = falling->pivot_y + 1;

			falling->rot3_x = falling->pivot_x;
			falling->rot3_y = falling->pivot_y + 2;

		}
	}
}

void l_rotate(tetromino* falling, int* grid)
{
	int check;
	check = 0;

	if(falling->orientation == NO_TURNS)
	{
		check += (falling->pivot_x + 2 >= MAXCOL)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x + 2) == FULL)? 1:0;

		check += (falling->pivot_x + 1 >= MAXCOL)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x + 1) == FULL)? 1:0;

		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = ONE_TURN;

			falling->rot1_x = falling->pivot_x + 2;
			falling->rot1_y = falling->pivot_y;

			falling->rot2_x = falling->pivot_x + 1;
			falling->rot2_y = falling->pivot_y;

			falling->rot3_x = falling->pivot_x;
			falling->rot3_y = falling->pivot_y + 1;
		}

	}
	else if(falling->orientation == ONE_TURN)
	{
		check += (falling->pivot_y + 2 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 2, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = TWO_TURNS;

			falling->rot1_x = falling->pivot_x;
			falling->rot1_y = falling->pivot_y + 2;

			falling->rot2_x = falling->pivot_x;
			falling->rot2_y = falling->pivot_y + 1;

			falling->rot3_x = falling->pivot_x - 1;
			falling->rot3_y = falling->pivot_y;
		}
	}
	else if(falling->orientation == TWO_TURNS)
	{
		check += (falling->pivot_x - 2 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 2) == FULL)? 1:0;

		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		check += (falling->pivot_y - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = THREE_TURNS;

			falling->rot1_x = falling->pivot_x - 2;
			falling->rot1_y = falling->pivot_y ;

			falling->rot2_x = falling->pivot_x - 1;
			falling->rot2_y = falling->pivot_y;

			falling->rot3_x = falling->pivot_x;
			falling->rot3_y = falling->pivot_y - 1;
		}
	}
	else // THREE_TURNS
	{
		check += (falling->pivot_y - 2 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 2, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_y - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_x + 1 > MAXCOL)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x + 1) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = NO_TURNS;

			falling->rot1_x = falling->pivot_x;
			falling->rot1_y = falling->pivot_y - 2;

			falling->rot2_x = falling->pivot_x;
			falling->rot2_y = falling->pivot_y - 1;

			falling->rot3_x = falling->pivot_x + 1;
			falling->rot3_y = falling->pivot_y;
		}
	}
}

void t_rotate(tetromino* falling, int* grid)
{
	
	int check;
	check = 0;

	if(falling->orientation == NO_TURNS)
	{
		check += (falling->pivot_y - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = ONE_TURN;

			falling->rot1_x = falling->pivot_x;
			falling->rot1_y = falling->pivot_y - 1;

			falling->rot2_x = falling->pivot_x;
			falling->rot2_y = falling->pivot_y + 1;

			falling->rot3_x = falling->pivot_x - 1;
			falling->rot3_y = falling->pivot_y;
		}
	}
	else if(falling->orientation == ONE_TURN)
	{
		check += (falling->pivot_x + 1 >= MAXCOL)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x + 1) == FULL)? 1:0;

		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		check += (falling->pivot_y - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = TWO_TURNS;

			falling->rot1_x = falling->pivot_x + 1;
			falling->rot1_y = falling->pivot_y;

			falling->rot2_x = falling->pivot_x - 1;
			falling->rot2_y = falling->pivot_y;

			falling->rot3_x = falling->pivot_x;
			falling->rot3_y = falling->pivot_y - 1;
		}
	}
	else if(falling->orientation == TWO_TURNS)
	{
		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_y - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_x + 1 >= MAXCOL)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x + 1) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = THREE_TURNS;

			falling->rot1_x = falling->pivot_x;
			falling->rot1_y = falling->pivot_y + 1;

			falling->rot2_x = falling->pivot_x;
			falling->rot2_y = falling->pivot_y - 1;

			falling->rot3_x = falling->pivot_x + 1;
			falling->rot3_y = falling->pivot_y;
		}
	}
	else
	{
		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		check += (falling->pivot_x + 1 >= MAXCOL)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x + 1) == FULL)? 1:0;

		check += (falling->pivot_y + 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = NO_TURNS;

			falling->rot1_x = falling->pivot_x - 1;
			falling->rot1_y = falling->pivot_y ;

			falling->rot2_x = falling->pivot_x + 1;
			falling->rot2_y = falling->pivot_y;

			falling->rot3_x = falling->pivot_x;
			falling->rot3_y = falling->pivot_y + 1;
		}
	}
}

void rl_rotate(tetromino* falling, int* grid)
{
	int check;
	check = 0;

	if(falling->orientation == NO_TURNS)
	{
		check += (falling->pivot_x + 2 >= MAXCOL)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x + 2) == FULL)? 1:0;

		check += (falling->pivot_x + 1 >= MAXCOL)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x + 1) == FULL)? 1:0;

		check += (falling->pivot_y - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = ONE_TURN;

			falling->rot1_x = falling->pivot_x + 2;
			falling->rot1_y = falling->pivot_y;

			falling->rot2_x = falling->pivot_x + 1;
			falling->rot2_y = falling->pivot_y;

			falling->rot3_x = falling->pivot_x;
			falling->rot3_y = falling->pivot_y - 1;
		}
	}
	else if(falling->orientation == ONE_TURN)
	{
		check += (falling->pivot_y + 2 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 2, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_x + 1 >= MAXCOL)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x + 1) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = TWO_TURNS;

			falling->rot1_x = falling->pivot_x;
			falling->rot1_y = falling->pivot_y + 2;

			falling->rot2_x = falling->pivot_x;
			falling->rot2_y = falling->pivot_y + 1;

			falling->rot3_x = falling->pivot_x + 1;
			falling->rot3_y = falling->pivot_y;
		}
	}
	else if(falling->orientation == TWO_TURNS)
	{
		check += (falling->pivot_x - 2 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 2) == FULL)? 1:0;

		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = THREE_TURNS;

			falling->rot1_x = falling->pivot_x - 2;
			falling->rot1_y = falling->pivot_y;

			falling->rot2_x = falling->pivot_x - 1;
			falling->rot2_y = falling->pivot_y;

			falling->rot3_x = falling->pivot_x;
			falling->rot3_y = falling->pivot_y + 1;
		}
	}
	else
	{
		check += (falling->pivot_y - 2 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 2, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_y - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = NO_TURNS;

			falling->rot1_x = falling->pivot_x;
			falling->rot1_y = falling->pivot_y - 2;

			falling->rot2_x = falling->pivot_x;
			falling->rot2_y = falling->pivot_y - 1;

			falling->rot3_x = falling->pivot_x - 1;
			falling->rot3_y = falling->pivot_y;
		}
	}
}

void z_rotate(tetromino* falling, int* grid)
{
	int check;
	check = 0;

	if(falling->orientation ==  NO_TURNS)
	{
		check += (falling->pivot_y - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x - 1) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = ONE_TURN;

			falling->rot1_x = falling->pivot_x;
			falling->rot1_y = falling->pivot_y - 1;

			falling->rot2_x = falling->pivot_x - 1;
			falling->rot2_y = falling->pivot_y;

			falling->rot3_x = falling->pivot_x - 1;
			falling->rot3_y = falling->pivot_y + 1;
		}
	}
	else //if(falling->orientation == ONE_TURN)
	{
		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_x + 1 >= MAXCOL)? 1:0;
		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x + 1) == FULL)? 1:0;

		if(check == 0)
		{
			falling->orientation = NO_TURNS;

			falling->rot1_x = falling->pivot_x - 1;
			falling->rot1_y = falling->pivot_y;

			falling->rot2_x = falling->pivot_x;
			falling->rot2_y = falling->pivot_y + 1;

			falling->rot3_x = falling->pivot_x + 1;
			falling->rot3_y = falling->pivot_y + 1;
		}
	}/*
	else if(falling->orientation == TWO_TURNS)
	{

	}
	else
	{

	}*/
}

void s_rotate(tetromino* falling, int* grid)
{
	int check;
	check = 0;

	if(falling->orientation == NO_TURNS)
	{
		check += (falling->pivot_y + 1 >= MAXROW)? 1:0; //rot1
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL)? 1:0;

		check += (falling->pivot_y - 1 < 0)? 1:0;  //rot2
		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y - 1, falling->pivot_x - 1) == FULL)? 1:0;

		check += (falling->pivot_x - 1 < 0)? 1:0;  //rot3
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x - 1) == FULL)? 1:0;

		if(check == 0) //safe to modify
		{
			falling->orientation = ONE_TURN;

			falling->rot1_x = falling->pivot_x;
			falling->rot1_y = falling->pivot_y + 1;

			falling->rot2_x = falling->pivot_x - 1;
			falling->rot2_y = falling->pivot_y - 1;

			falling->rot3_x = falling->pivot_x - 1;
			falling->rot3_y = falling->pivot_y;

		}
	}
	else
	{
		check += (falling->pivot_x + 1 >= MAXCOL)? 1:0; //rot1
		check += (grid_get(grid, falling->pivot_y, falling->pivot_x + 1) == FULL)? 1:0;

		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;  //rot2
		check += (falling->pivot_x - 1 < 0)? 1:0;
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x - 1) == FULL)? 1:0;

		check += (falling->pivot_y + 1 >= MAXROW)? 1:0;  //rot3
		check += (grid_get(grid, falling->pivot_y + 1, falling->pivot_x) == FULL)? 1:0;

		if(check == 0) //safe to modify
		{
			falling->orientation = NO_TURNS;

			falling->rot1_x = falling->pivot_x + 1;
			falling->rot1_y = falling->pivot_y;

			falling->rot2_x = falling->pivot_x - 1;
			falling->rot2_y = falling->pivot_y + 1;

			falling->rot3_x = falling->pivot_x;
			falling->rot3_y = falling->pivot_y + 1;

		}
	}
}

