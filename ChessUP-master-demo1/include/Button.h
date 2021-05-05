#include "../include/common.h"

#include "../include/GameState.h"
#include "../include/Piece.h"


#ifndef BUTTON_H
#define BUTTON_H

#include <SDL_ttf.h>
#include <string>

enum class ButtonSprite
{
    BUTTON_SPRITE_PVP,
    BUTTON_SPRITE_CPU,
    BUTTON_SPRITE_CHESSUP,
    BUTTON_SPRITE_QUIT,
    BUTTON_SPRITE_CONTINUE,
    BUTTON_SPRITE_SAVE,
    BUTTON_SPRITE_LOAD,
    BUTTON_SPRITE_MAIN_MENU,
    BUTTON_SPRITE_TOTAL
};

enum class Color
{
    BLACK_COLOR,
    WHITE_COLOR,
    RED_COLOR,
    GREEN_COLOR,
    BLUE_COLOR,
    SILVER_COLOR,
    GRAY_COLOR,
    DEEPPINK_COLOR,
    LIGHTPINK_COLOR
};

class Button
{
public:
    // button defautf position
    int x_button_;
    int y_button_;
    // Current used global sprite
    ButtonSprite mCurrentSprite_;

    // Initializes variables
    Button();
    Button(int x, int y);
    // Deallocates memory
    ~Button();

    Texture createTextTexture();

    // Check inside
    bool isInside(SDL_Event *e, int size);
    // Handles mouse event
    void handleEvent(SDL_Event* e, GameState* gm);
    // Shows button sprite
    void render();
    void renderButton();

    // Sets top left position
    void setPosition(int x, int y) { mPosition_.x = x; mPosition_.y = y; }
    // Sets the current sprite
    void setCurrentSprite(ButtonSprite sprite) { mCurrentSprite_ = sprite; }
    // Sets text
    void setText(std::string text) {mTextStr_ = text;}
    // Sets color
    void setColor(Color type);

private:
    int check = 0;
    // Top left position
    SDL_Point mPosition_;

    // Texture
    Texture mText_;
    // Text string
    std::string mTextStr_;
    // Text color
    SDL_Color mTextColor_;
};

#endif // BUTTON_H
