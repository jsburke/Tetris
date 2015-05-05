This is an implementation of Tetris in C using SDL2.

In order for this to compile, you must have the proper packages installed for SDL.  Probably the easiest guide to follow for this can be found here:
http://lazyfoo.net/tutorials/SDL/01_hello_SDL/

This will guide you based on your system and IDE, if needed.

For this particular project, the Makefile is set up to compile with gcc on a windows machine.  To compile on a Linux machine, prospectively, remove the following from the Makefile:

- The Include Paths
- Only compiler flag is -w, remove if you want warnings
- Only Linker flag is -lSDL2

// -------------------

 5-5-2015
 
 I plan on some major revisions to this project to organize the code and better use SDL soon.  This is my checklist:
 
 o Single image file that SDL will clip into
 o Wall-Kick
 o Floor Kick
 o A "Tetris_def.h" to include the grid and tetromino headers along with other game controlling values like DROP_SCALER.
 o Looking to revise the main game loop into a function that leverages tail optimization.  Looking to ATS implementation
 o Better usage of some of the SDL structures.  Many unneeded globals that.
 o Debating using SDL to control the frame rate
 o A Hold tetromino so beloved long blocks can be saved for when they are useful
 o MINOR: better speed algorithms.  They are slow to start and ridiculous around 7k points
 o MINOR: debating removing point accrual simply for tetrominos being placed
 o MINOR: points for T spins and the like
