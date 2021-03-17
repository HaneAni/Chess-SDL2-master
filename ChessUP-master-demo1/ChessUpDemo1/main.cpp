#include "SDL_utils.h"
#include "common.h"

#include "ChessBoard.h"
#include "States.h"

#ifndef SDL_INCLUDES
#define SDL_INCLUDES
#include <SDL_image.h>
#include <SDL.h>
#endif

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
            gm->startGameState(GameMode::GAME_MODE_PVP);
    	}

    	// Release resources and end sdl
        chessBoard->close();

	    return 0;
    }
}
