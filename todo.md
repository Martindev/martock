Martock: Development Schedule
================================================================================

Map Generation
--------------------------------------------------------------------------------
Before creating the engine, it needs data to work with. This stage is dedicated
to experimenting with and implementing cellular automata to generate endless
worlds which appear contiguous.

1. Compose a format for storing and loading the maps, which will be 3D arrays
   stored in "chunks", X by Y by Z. They will be illustrated and navigated in 2D
   but some features of the game will require a back layer and metadata.

2. The map storing and loading algorithm must be highly configurable, taking
   arguments for the size of a block (for example, if we decide to make a struct
   for it in the future and add/remove fields), and dimensions of the chunk. A
   potential prototype is below.

        struct Chunk {
                int width;
                int height;
                int depth;
                size_t block_size;
                Block *grid[width][height][depth];
        };
    
   So the size of a chunk file can be determined by width x height x depth x
   block_size.

3. The functions for generating chunks, or chunk regions, must take other chunks
   as arguments to ensure the generated chunk matches the chunks next to it.

4. Tile graphics will be required, at least basic ones, including but not
   limited to sky, cloud, grass, dirt, grass edges on dirt, stone, and a few
   kinds of ore.

5. There must be a module for rendering maps to images for analyzing them from
   aesthetic point of view. This should probably be done earlier rather than
   later as it will make testing far easier.

Camera
--------------------------------------------------------------------------------
A camera must exist for browsing the map and testing the real-time generation
performance. It must be able to roam using keyboard keys endlessly (requiring
that new chunks generate to for it in real time).

1. The camera will have a crosshair or pointer which targets the block it rests
   on, and reports the coordinates.

2. The camera must be able to change the block type, based on the one it is
   currently aimed at.

3. The graphical window must be resizeable, and doing so cannot adjust the
   position of the camera in any unnatural way.

Interfaces
--------------------------------------------------------------------------------
Create a convenient interface for the current state of the program. This will be
built on and expanded as more modes are added.

1. A main menu, leading to the camera mode and dummy launchers for singleplayer
   and multiplayer.

2. An escape menu for the camera, including options to quit, adjust video
   options, and return to the main menu.

3. Add a command system which can later be used for debugging.
