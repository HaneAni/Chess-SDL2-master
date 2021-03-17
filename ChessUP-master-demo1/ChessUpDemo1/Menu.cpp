#include "Menu.h"

Menu::Menu()
{
    mPosition_.x = 0;
    mPosition_.y = 0;

    mCurrentSprite_ = MenuSprite::MENU_SPRITE_MAIN_MENU;
}

Menu::~Menu()
{
}

void Menu::handleEvent(SDL_Event* e, GameState* gm)
{
    check = 0;
    // If mouse event happened
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
    {
        // Gets mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        // Check outside the menu box
        if( (x < mPosition_.x) || (x > mPosition_.x + MENU_WIDTH) || (y < mPosition_.y) || (y > mPosition_.y + MENU_HEIGHT) )
            inside = false;

        if(inside)
        {
            check = 1;
            // Set mouse over sprite
            switch (e->type)
            {
            case SDL_MOUSEMOTION :
                break;
            case SDL_MOUSEBUTTONDOWN :
                switch (mCurrentSprite_)
                {
                case MenuSprite::MENU_SPRITE_PVP :
                    gm->setGameState(GameMode::GAME_MODE_PVP);
                    break;
                case MenuSprite::MENU_SPRITE_CPU :
                    gm->setGameState(GameMode::GAME_MODE_CPU);
                    break;
                case MenuSprite::MENU_SPRITE_CHESSUP :
                    gm->setGameState(GameMode::GAME_MODE_CHESSUP);
                    break;
                case MenuSprite::MENU_SPRITE_QUIT :
                    gm->setGameState(GameMode::GAME_MODE_QUIT);
                    break;
                case MenuSprite::MENU_SPRITE_CONTINUE :
                    gm->isPause = 0;
                    //gm->setGameState(GameMode::GAME_MODE_CONTINUE);
                    break;
                case MenuSprite::MENU_SPRITE_SAVE :
                    gm->isPause = 0;
                    gm->setGameState(GameMode::GAME_MODE_SAVE);
                    break;
                case MenuSprite::MENU_SPRITE_LOAD :
                    gm->isPause = 0;
                    gm->setGameState(GameMode::GAME_MODE_LOAD);
                    break;
                case MenuSprite::MENU_SPRITE_MAIN_MENU :
                    gm->isPause = 0;
                    gm->setGameState(GameMode::GAME_MODE_MAIN_MENU);
                    break;
                }
                //mCurrentSprite = BUTTON_SPRITE_SAVE;
                break;
            }
        }
    }
}

void Menu::render()
{
    // Show current button sprite
    g_MenuSpriteSheetTexture.render(mPosition_.x, mPosition_.y, &(g_SpriteClips[(int) mCurrentSprite_]));

    if(check == 1){
        blackPieces[(int) PieceName::KNIGHT].render(mPosition_.x + MENU_WIDTH/2 - 40 ,mPosition_.y);
    }
}
