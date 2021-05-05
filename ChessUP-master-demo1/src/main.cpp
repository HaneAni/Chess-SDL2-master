#include "../include/SDL_utils.h"
#include "../include/common.h"

#include "../include/ChessBoard.h"
#include "../include/States.h"

#ifndef SDL_INCLUDES
#define SDL_INCLUDES
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#endif // SDL_INCLUDES

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    ChessBoard *chessBoard = new ChessBoard();

    GameState *gm = new GameState();

	if(!chessBoard->init()) {
		cout << "Failed to init" << endl;
	}
	else {
		// Load media
		if(!chessBoard->loadImage()) {
			cout << "Failed to load media" << endl;
		}
		else {
            gm->startGameState(GameMode::GAME_MODE_MAIN_MENU);
    	}

    	// Release resources and end sdl
        chessBoard->close();
    }
    return 0;
}
