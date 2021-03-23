#include "Texture.h"
#include "common.h"

#ifndef GAME_STATE_H
#define GAME_STATE_H


enum class GameMode
{
    GAME_MODE_PVP,
    GAME_MODE_CPU,
    GAME_MODE_CHESSUP,
    GAME_MODE_QUIT,
    GAME_MODE_CONTINUE,
    GAME_MODE_SAVE,
    GAME_MODE_LOAD,
    GAME_MODE_MAIN_MENU,
    GAME_MODE_PAUSE,
    GAME_MODE_TOTAL
};

// Control the game state
class GameState
{
public:
    GameState();
    ~GameState();

    int isPause;

    void startGameState(GameMode playMode);

    GameMode getGameState() {return gameState_;}

    void setGameState(GameMode gameMode) {gameState_ = gameMode;}

private:
    GameMode gameState_;

    void renderMainMenu();
    void renderPVP();
    void renderCPU();
    void renderChessupMode();
    void renderPauseMenu();

};

#endif // GAME_STATE_H

