=================================================================================
Author
=================================================================================
Name:  Yoan Bernatchez
Email: yoan_bernatchez@hotmail.com

=================================================================================
Project Settings
=================================================================================
Language: 		      C
IDE:			      Code::Blocks
Commenting style:             Doxygen
Indentation style:            K&R with indentation of the length of 4 characters
Naming and coding convention: GTK+ (with a variant on header style)
Max characters per line:      80 characters

Non-static functions, typedefs, enums and global macros are prefixed with eng_
(short for engine_) to prevent name duplicates.

NOTE:
You can run the demo game for the engine by opening the "Engine Demo.exe" file in
Portfolio/Engine Demo. This demo is released for Windows only at the moment.

=================================================================================
Summary of the Engine
=================================================================================
Supported Operating Systems: Windows OS (tested),  Mac OS (not tested),  Linux OS
		   	     (not tested)
Graphic library used:        SDL2

Description:    This engine  allows the user  to create a 2D game that works with
		tiles,  objects,  chunks,  characters, collision, pathfinding and
		hud elements.

=================================================================================
Engine Features
=================================================================================
Pathfinding:    Provides the user with a pathfinding algorithm (wave propagation)
	        that returns a path that can be used by NPCs.

Character:      Provides the user  with an  easy  way  to  implement  characters.
	        Characters have  collision, can be  rendered to the screen easily
                and have other useful functionalities.

Chunks:	        Provides the user with a way to  easily load tiles and objects to
                a chunk from a formatted file. Tiles and objects can be displayed
                on screen.

Collision:      Provides an easy way  to check collision  between a character and
                tiles in the chunks.

File utilities: Provides some basic  file utilities  such as finding a  word in a
		file, replacing a word in a file and deleting parts of a file.

Hud:	     	Provides the  user  with an  easy way  to create  graphic windows
		containing images, text, and other hud object types. The huds can
		be printed on screen and is made of a structure containing useful
		modifyable members such as opacity, size, etc.

Render:      	Provides the user with rendering functions that take in parameters
		chunks and characters, decide of the rendering order and print  it
		on the screen.

Time:	     	Provides some  simple time  functionnalities  such as  checking if
		time has elapsed since last checking a timer.

=================================================================================
TODO
=================================================================================
- Make an error handling system.
- Make the number of chunks variable (currently can only work with exactly 4).
- Implement support for object collision.
- Implement sound functionnalities.
- Implement particles
