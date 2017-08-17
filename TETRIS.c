#ifdef ENV_WINDOWS
	#include <SDL.h>
#elif ENV_LINUX
	#include <SDL2/SDL.h>
#endif

#include <stdio.h>

#include "tetromino.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

#define BLOCK_SIZE      22
#define INDENT          20
#define PREVIEW_OFFSET  50  
#define SCORE_X			MAXCOL * BLOCK_SIZE + 250
#define SCORE_Y			250
#define NUM_WIDTH		15
#define DROP_RATE		600
#define DROP_SCALER             15
#define LOCK_RATE		200
#define KEY_RATE        50


enum keypress_type{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ESC,
	SPACE
};



//FILE;

//SDL functions

int init();
int load_media();
void game_close();

// blit functions

void blit_preview(int); 
void blit_grid(int*);   // may require alterations after grid.h is in
void blit_tetromino(tetromino*);
void blit_score(int);

// game control functions
int row_check(int*);
void tetromino_init(tetromino*, tetromino*, tetromino*);
int auto_drop(tetromino*, int*, int, int);


// SDL Windows and surfaces
SDL_Window*  MainWin       = NULL;
// suface contained by the window
SDL_Surface* ScreenSurface = NULL;
// Images that correspond preview block
SDL_Surface* PreviewSurfaces[BLOCK_TYPE_TOTAL];
SDL_Surface* scoreSurfaces[10]; // one for each 0-9
SDL_Surface* Preview       = NULL;
SDL_Surface* full          = NULL;
SDL_Surface* empty         = NULL;
SDL_Surface* tetromino_bmp = NULL;
SDL_Rect     prevRect, gridRect, fallingRect, scoreRect;

//---------------------------

int main(int argc, char* argv[])
{

	// SDL Event handler
	SDL_Event    event;
	int key_press;

	int game_over, score;
	int game_grid[CELLS] = {0};
	int row_test, last_row, drop_count, lock_in, key_count;
	int first_hold = 1;

	tetromino * falling;
	tetromino * next;
	tetromino * hold;
	tetromino * temp;

	set_rand();
	lock_in = 0;
	drop_count = 1;
	game_over = 0;
	key_count = 0;
	score     = 0;

	falling = tetromino_new(ACTIVE);
	next    = tetromino_new(INACTIVE);
	hold    = tetromino_new(INACTIVE);
	temp    = NULL;
	
	//log = fopen("Log.txt","w");
	//fprintf(log, "Begin Main\n");

	if(init() == 0)
	{//printf(log, "SDL did not initialize.\n" );
		return 0;
	}

	if(load_media() == 0)
	{//printf(log, "Media Loading failed\n" );
		return 0;
	}


	gridRect.x = 0;
	gridRect.y = 0;

	fallingRect.x = 0;
	fallingRect.y = 0;

	prevRect.x = (BLOCK_SIZE*MAXCOL) + PREVIEW_OFFSET;
	prevRect.y = 100;

	scoreRect.x = SCORE_X;
	scoreRect.y = SCORE_Y;

//	Preview = PreviewSurfaces[SQUARE_BLOCK]; // set a dummy default

	//anim = 0;
	//fprintf(log, "Game Loop entry\n" );

	while(game_over == 0)
	{
		/*if(anim ==  0)
			tetromino_drop(falling, game_grid);

		anim = (anim == 200)? 0: anim+1;*/

		drop_count = auto_drop(falling, game_grid, drop_count, score);

		key_press = 100;

		if(SDL_PollEvent(&event) != 0)
		{
			switch(event.type)
			{
				case SDL_QUIT:
					game_over = 1;
				break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_UP:
							key_press = UP;
						break;

						case SDLK_DOWN:
							key_press = DOWN;
						break;

						case SDLK_LEFT:
							key_press = LEFT;
						break;

						case SDLK_RIGHT:
							key_press = RIGHT;
						break;

						case SDLK_ESCAPE:
							key_press = ESC;
						break;
						
						case SDLK_SPACE:
							key_press = SPACE;
						break;
					}
				break;
			}
		}

		//if(key_count == 0)
		//{
			switch(key_press)
				{
					case UP:
						tetromino_rotate(falling, game_grid);
					break;
	
					case DOWN:
						tetromino_drop(falling, game_grid);
					break;
	
					case RIGHT:
						tetromino_shift_right(falling, game_grid);
					break;
	
					case LEFT:
						tetromino_shift_left(falling, game_grid);
					break;
	
					case ESC:
					game_over = 1;
					break;
					
					case SPACE: // this still would be nice with visuals...
						if(first_hold == 1)
						{
							temp = hold;
							tetromino_mod(temp);
							hold = falling;
							falling = next;
							tetromino_activate(falling);
							next = temp;
							temp = NULL;
							first_hold = 0;
						}
						else
						{
							temp = falling;
							falling = hold;
							tetromino_activate(falling);
							hold = temp;
							temp = NULL;
						}
					break;
			}
		//}

		key_count = (key_count < KEY_RATE) ? key_count + 1: 0;

		lock_in = (tetromino_lock(falling, game_grid) == 1)? lock_in+1:0;
		
		if(lock_in == 200)
		{
			tetromino_into_grid(falling, game_grid);
			score += falling->shape + 2 * 3;
			score += row_check(game_grid);
			// manage the tetrominos
			temp = falling;
			falling = next;
			tetromino_activate(falling);
			tetromino_mod(temp);
			next = temp;
			temp = NULL;
			lock_in = 0;
		}

		if(grid_row_any(game_grid,0) == 1)
			game_over = 1;

		//blit to screen
		SDL_FillRect(ScreenSurface, 0, 0); // so the images don't trail
		blit_preview(next->shape);	
		blit_grid(game_grid);
		blit_tetromino(falling);
		blit_score(score);
		SDL_UpdateWindowSurface(MainWin);
	}

	game_close();
	free(falling);
	free(next);
	free(hold);
	return 0;
}

int init()
{
	int success = 1;

	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		//fprintf(log, "SDL INIT VIDEO Failed.  Error: %s\n", SDL_GetError() );
		success = 0;
	}
	else
	{
		MainWin = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(MainWin == NULL)
		{
			//fprintf(log, "Window not made.  Error: %s\n", SDL_GetError() );
			success = 0;
		}
		else
		{
			ScreenSurface = SDL_GetWindowSurface(MainWin);
		}
	}

	return success;
}

int load_media()
{
	full = SDL_LoadBMP( "full.bmp" );
	if(full == NULL){
		//fprintf(log, "full failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	empty = SDL_LoadBMP( "empty.bmp" );
	if(empty == NULL){
		//fprintf(log, "empty failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	tetromino_bmp = SDL_LoadBMP( "tetromino.bmp" );
	if(tetromino_bmp == NULL){
		//fprintf(log, "tetromino_bmp failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	// tetrominos

	PreviewSurfaces[LONG_BLOCK] = SDL_LoadBMP("LONG.bmp");
	if(PreviewSurfaces[LONG_BLOCK] == NULL){
		//fprintf(log, "long block failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	PreviewSurfaces[L_BLOCK] = SDL_LoadBMP("L.bmp");
	if(PreviewSurfaces[L_BLOCK] == NULL){
		//fprintf(log, "l block failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	PreviewSurfaces[RL_BLOCK] = SDL_LoadBMP("RL.bmp");
	if(PreviewSurfaces[RL_BLOCK] == NULL){
		//fprintf(log, "RL block failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	PreviewSurfaces[S_BLOCK] = SDL_LoadBMP("S.bmp");
	if(PreviewSurfaces[S_BLOCK] == NULL){
		//fprintf(log, "S block failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	PreviewSurfaces[Z_BLOCK] = SDL_LoadBMP("Z.bmp");
	if(PreviewSurfaces[Z_BLOCK] == NULL){
		//fprintf(log, "Z block failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	PreviewSurfaces[T_BLOCK] = SDL_LoadBMP("T.bmp");
	if(PreviewSurfaces[T_BLOCK] == NULL){
		//fprintf(log, "T block failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	PreviewSurfaces[SQUARE_BLOCK] = SDL_LoadBMP("SQUARE.bmp");
	if(PreviewSurfaces[SQUARE_BLOCK] == NULL){
		//fprintf(log, "square block failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	scoreSurfaces[0] = SDL_LoadBMP("zero.bmp");
	if(scoreSurfaces[0] == NULL){
		//fprintf(log, "0 failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	scoreSurfaces[1] = SDL_LoadBMP("one.bmp");
	if(scoreSurfaces[1] == NULL){
		//fprintf(log, "1 failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	scoreSurfaces[2] = SDL_LoadBMP("two.bmp");
	if(scoreSurfaces[2] == NULL){
		//fprintf(log, "2 failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	scoreSurfaces[3] = SDL_LoadBMP("three.bmp");
	if(scoreSurfaces[3] == NULL){
		//fprintf(log, "3 failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	scoreSurfaces[4] = SDL_LoadBMP("four.bmp");
	if(scoreSurfaces[4] == NULL){
		//fprintf(log, "4 failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	scoreSurfaces[5] = SDL_LoadBMP("five.bmp");
	if(scoreSurfaces[5] == NULL){
		//fprintf(log, "5 failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	scoreSurfaces[6] = SDL_LoadBMP("six.bmp");
	if(scoreSurfaces[6] == NULL){
		//fprintf(log, "6 failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	scoreSurfaces[7] = SDL_LoadBMP("seven.bmp");
	if(scoreSurfaces[7] == NULL){
		//fprintf(log, "7 failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	scoreSurfaces[8] = SDL_LoadBMP("eight.bmp");
	if(scoreSurfaces[8] == NULL){
		//fprintf(log, "8 failed. Error: %s\n", SDL_GetError());
		return 0;
	}

	scoreSurfaces[9] = SDL_LoadBMP("nine.bmp");
	if(scoreSurfaces[9] == NULL){
		//fprintf(log, "9 failed. Error: %s\n", SDL_GetError());
		return 0;
	}
	return 1;
}

void game_close()
{
	int i;
	for(i = 0; i < BLOCK_TYPE_TOTAL; i++)
	{
		SDL_FreeSurface(PreviewSurfaces[i]);
		PreviewSurfaces[i] = NULL;
	}

	SDL_FreeSurface(full);
	SDL_FreeSurface(empty);
	SDL_DestroyWindow(MainWin);
	MainWin = NULL;

	SDL_Quit();
}

// blitting functions

void blit_preview(int type)
{
	Preview = PreviewSurfaces[type];
	SDL_BlitSurface(Preview, NULL, ScreenSurface, &prevRect);
}

void blit_grid(int* grid)
{
	int i;

	for(i = 0; i < CELLS; i++)
	{
		
		gridRect.x = grid_offset_2_x(i) * BLOCK_SIZE + INDENT;
		gridRect.y = grid_offset_2_y(i) * BLOCK_SIZE + INDENT;
		if(grid[i] == FULL) // later to FULL
		{
			SDL_BlitSurface(full, NULL, ScreenSurface, &gridRect);
		}
		else
		{
			SDL_BlitSurface(empty, NULL, ScreenSurface, &gridRect);
		}
	}
}

void blit_tetromino(tetromino* cur)
{
	fallingRect.x = cur->pivot_x * BLOCK_SIZE + INDENT;
	fallingRect.y = cur->pivot_y * BLOCK_SIZE + INDENT;
	SDL_BlitSurface(tetromino_bmp, NULL, ScreenSurface, &fallingRect);

	fallingRect.x = cur->rot1_x * BLOCK_SIZE + INDENT;
	fallingRect.y = cur->rot1_y * BLOCK_SIZE + INDENT;
	SDL_BlitSurface(tetromino_bmp, NULL, ScreenSurface, &fallingRect);

	fallingRect.x = cur->rot2_x * BLOCK_SIZE + INDENT;
	fallingRect.y = cur->rot2_y * BLOCK_SIZE + INDENT;
	SDL_BlitSurface(tetromino_bmp, NULL, ScreenSurface, &fallingRect);

	fallingRect.x = cur->rot3_x * BLOCK_SIZE + INDENT;
	fallingRect.y = cur->rot3_y * BLOCK_SIZE + INDENT;
	SDL_BlitSurface(tetromino_bmp, NULL, ScreenSurface, &fallingRect);

}

int row_check(int* game_grid)
{
	int i, rows_cleared, points;
	rows_cleared = 0;
	points = 0;

	for(i = 0; i < MAXROW; i++)
	{
		if(grid_row_full(game_grid, i) == 1)
		{
			grid_row_clear(game_grid, i);
			points += 25;
			rows_cleared += 1;
			row_bubble_up(game_grid, i);
		}
	}
	return points * rows_cleared * rows_cleared ;
}

void row_bubble_up(int* game_grid, int row)
{
	int i;

	for(i = row; i > 0 ; i--)
	{
		grid_row_swap(game_grid, i, i - 1);
	}
}

void blit_score(score)
{
	int disp;
	scoreRect.x = SCORE_X;

	while(score > 0)
	{
		disp = score % 10;
		score /= 10;

		SDL_BlitSurface(scoreSurfaces[disp], NULL, ScreenSurface, &scoreRect);

		scoreRect.x -= NUM_WIDTH;
	}
}

int auto_drop(tetromino * falling, int* game_grid, int drop_count, int score)
{
	if(drop_count == 0)
		tetromino_drop(falling, game_grid);

	drop_count = (drop_count + score / DROP_SCALER >= DROP_RATE)? 0:drop_count + 1;
}
