Trương Minh Đức - 20020396
Trường Đại học Công Nghệ - ĐHQGHN

CHESS by HaneAni


A simple Chess implementation I made for an university project.
I used SDL2 and C++.
The original project is here: https://github.com/HaneAni/Chess-SDL2-master

-----------

**The files are organized this way:**

*	Chessup-Master-Demo -> file project
*	SDL2_lib -> include librarys of SDL2
*	include -> header files
*	res -> images, sounds and fonts files
*	src -> main and source codes

-----------

**Requirements:**
	
* C++
* SDL2
* SDL2-IMAGE
* SDL2-TTF
* SDL2-MIXER
 
Check the correct package name of the SDL libraries. On arch based distros the packages are: SDL2, SDL2_image, SDL2_ttf, SDL2_mixer.

**Compile and run**
	
* go to the Chessup-Master-Demo directory.
* run Chessup-Master-Demo.exe
* you can compile and run the tests project located at Chessup-Master-Demo/Chessup-Master-Demo.cbp.
	
**Ingame commands:**

* esc -> pause game
* z -> undo movement

PVP mode
CPU mode:
* Alpha-beta algorithm

Edit mode:
* left and right -> select the piece
* up and down -> select the color
* click -> place the piece.
* enter -> done, start a pvp mode after editing the piece positions
    
-----------

