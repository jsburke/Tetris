This is an implementation of Tetris in C using SDL2.

In order for this to compile, you must have the proper packages installed for SDL.  Probably the easiest guide to follow for this can be found here:
http://lazyfoo.net/tutorials/SDL/01_hello_SDL/

This will guide you based on your system and IDE, if needed.

For this particular project, the Makefile is set up to compile with gcc on a windows machine.  To compile on a Linux machine, prospectively, remove the following from the Makefile:

- The Include Paths
- Only compiler flag is -w, remove if you want warnings
- Only Linker flag is -lSDL2
