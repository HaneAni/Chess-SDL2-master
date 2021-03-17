#include "GameState.h"
#include "Piece.h"

#include "common.h"

#ifndef MENU_H
#define MENU_H

//#include <string>

enum class MenuSprite
{
    MENU_SPRITE_PVP,
    MENU_SPRITE_CPU,
    MENU_SPRITE_CHESSUP,
    MENU_SPRITE_QUIT,
    MENU_SPRITE_CONTINUE,
    MENU_SPRITE_SAVE,
    MENU_SPRITE_LOAD,
    MENU_SPRITE_MAIN_MENU,
    MENU_SPRITE_TOTAL = 8
};

class Menu
{
public:
    // Initializes variables
    Menu();
    // Deallocates memory
    ~Menu();

    // Handles mouse event
    void handleEvent(SDL_Event* e, GameState* gm);

    // Shows menu sprite
    void render();

    // Sets top left position
    void setPosition(int x, int y) { mPosition_.x = x; mPosition_.y = y; }

    // Sets the current sprite
    void setCurrentSprite(MenuSprite sprite) { mCurrentSprite_ = sprite; }

private:
    // Top left position
    SDL_Point mPosition_;

    // Current used global sprite
    MenuSprite mCurrentSprite_;

    int check = 0;

};

#endif // MENU_H
