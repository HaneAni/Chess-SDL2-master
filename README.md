**Trương Minh Đức - 20020396**
**Trường Đại học Công Nghệ - ĐHQGHN**

CHESS by HaneAni

A simple Chess implementation I made for an university project.
I used SDL2 and C++.
The original project is here: https://github.com/HaneAni/Chess-SDL2-master

-----------

**The files are organized this way:**

* Chessup-Master-Demo -> file project
* SDL2_lib -> include librarys of SDL2
* include -> header files
* res -> images, sounds and fonts files
* src -> main and source codes

-----------

**Requirements:**
	
* C++
* SDL2
* SDL2-IMAGE
* SDL2-TTF
* SDL2-MIXER
 
Check the correct package name of the SDL libraries. On arch based distros the packages are: SDL2, SDL2_image, SDL2_ttf, SDL2_mixer.

**Compile and run**
	
* Go to the Chessup-Master-Demo directory.
* Run Chess.exe
* You can compile and run the tests project located at Chessup-Master-Demo/Chessup-Master-Demo.cbp.
	
**Ingame commands:**

* esc -> pause game.
* z -> undo movement.

PVP mode:
* Chess move
* King castling.
* Pawn transform.

CPU mode:
* Alpha-beta algorithm.

Edit mode:
* Left and right -> select the piece.
* Up and down -> select the color.
* Click -> place the piece.
* Enter -> done, start a pvp mode after editing the piece positions.
    
Save: Save the current chess board state.

Load: Upload a saved chess board state.

-----------

**Chess rules**

Chess move:
* King can move exactly one square horizontally, vertically, or diagonally. At most once in every game, each king is allowed to make a special move, known as castling.
* Queen can move any number of vacant squares diagonally, horizontally, or vertically.
* Rook can move any number of vacant squares vertically or horizontally. It also is moved while castling.
* Bishop can move any number of vacant squares in any diagonal direction.
* Knight can move one square along any rank or file and then at an angle. The knight´s movement can also be viewed as an "L" or "7" laid out at any horizontal or vertical angle.
* Pawns can move forward one square, if that square is unoccupied. If it has not yet moved, the pawn has the option of moving two squares forward provided both squares in front of the pawn are unoccupied. A pawn cannot move backward. Pawns are the only pieces that capture differently from how they move. They can capture an enemy piece on either of the two spaces adjacent to the space in front of them (i.e., the two squares diagonally in front of them) but cannot move to these spaces if they are vacant. The pawn is also involved in the two special moves en passant and promotion.

Castling:
* Neither king nor rook involved in castling may have moved from the original position.
* There must be no pieces between the king and the rook.

Pawn promotion:
* If a pawn reaches the opponent´s edge of the table, it will be promoted – the pawn may be converted to a queen, rook, bishop or knight, as the player desires. The choice is not limited to previously captured pieces. Thus its´ theoretically possible having up to nine queens or up to ten rooks, bishops, or knights if all pawns are promoted.

