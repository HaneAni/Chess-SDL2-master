#include "../include/Button.h"

Button::Button()
{
    x_button_ = (SCREEN_WIDTH - MENU_WIDTH) / 2;
    y_button_ = (SCREEN_HEIGHT - MENU_HEIGHT * TOTAL_MAIN_MENU - OFFSET * (TOTAL_MAIN_MENU - 1)) / 2;

    mPosition_.x = x_button_;
    mPosition_.y = y_button_;

    mCurrentSprite_ = ButtonSprite::BUTTON_SPRITE_MAIN_MENU;

    mTextColor_ = {0, 0, 0};
}

Button::Button(int x, int y)
{
    mPosition_.x = x;
    mPosition_.y = y;

    mCurrentSprite_ = ButtonSprite::BUTTON_SPRITE_MAIN_MENU;

    mTextColor_ = {0, 0, 0};
}

Button::~Button()
{
}

Texture Button::createTextTexture()
{
    //Render text
    if(!mText_.loadFromRenderedText(mTextStr_, mTextColor_, g_Font))
        logSDLError(std::cout, "Failed to render text texture!", TTF_ERROR, true);

    return mText_;
}

bool Button::isInside(SDL_Event *e, int size)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int button_width, button_height;

		if (size == SMALL_BUTTON)
		{
			button_width = SMALL_BUTTON_WIDTH;
			button_height = SMALL_BUTTON_HEIGHT;
		}
		else if (size == COMMON_BUTTON)
		{
			button_width = COMMON_BUTTON_WIDTH;
			button_height = COMMON_BUTTON_HEIGHT;
		}

		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < mPosition_.x || x > mPosition_.x + button_width || y < mPosition_.y || y > mPosition_.y + button_height)
			inside = false;

		return inside;
	}
	return false;
}

void Button::handleEvent(SDL_Event* e, GameState* gm)
{
    check = 0;
    // If mouse event happened
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
    {
        // Gets mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        // Check outside the button box
        if( (x < mPosition_.x || x > mPosition_.x + MENU_WIDTH) || (y < mPosition_.y || y > mPosition_.y + MENU_HEIGHT))
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
                case ButtonSprite::BUTTON_SPRITE_PVP :
                    gm->setGameState(GameMode::GAME_MODE_PVP);
                    break;
                case ButtonSprite::BUTTON_SPRITE_CPU :
                    gm->setGameState(GameMode::GAME_MODE_CPU);
                    break;
                case ButtonSprite::BUTTON_SPRITE_CHESSUP :
                    gm->setGameState(GameMode::GAME_MODE_CHESSUP);
                    break;
                case ButtonSprite::BUTTON_SPRITE_QUIT :
                    gm->setGameState(GameMode::GAME_MODE_QUIT);
                    break;
                case ButtonSprite::BUTTON_SPRITE_CONTINUE :
                    gm->isPause = 0;
                    break;
                case ButtonSprite::BUTTON_SPRITE_SAVE :
                    gm->isPause = 0;
                    gm->setGameState(GameMode::GAME_MODE_SAVE);
                    break;
                case ButtonSprite::BUTTON_SPRITE_LOAD :
                    gm->isPause = 0;
                    gm->setGameState(GameMode::GAME_MODE_LOAD);
                    break;
                case ButtonSprite::BUTTON_SPRITE_MAIN_MENU :
                    gm->isPause = 0;
                    gm->setGameState(GameMode::GAME_MODE_MAIN_MENU);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
    }
}

void Button::render()
{
    // Show current button sprite
    t_ButtonSpriteSheetTexture.render(mPosition_.x, mPosition_.y, &(g_SpriteClips[(int) mCurrentSprite_]));

    if(check == 1)
    {
        t_BlackPieces[(int) PieceName::KNIGHT].render(mPosition_.x + MENU_WIDTH/2 - 40 ,mPosition_.y);
    }
}

void Button::renderButton()
{
    SDL_SetRenderDrawColor(g_Renderer, 128, 128, 128, 255);

    SDL_Rect in_SpriteClips;
    in_SpriteClips.x = m_SpriteClips[(int) mCurrentSprite_].x + 5;
    in_SpriteClips.y = m_SpriteClips[(int) mCurrentSprite_].y + 5;
    in_SpriteClips.w = m_SpriteClips[(int) mCurrentSprite_].w - 10;
    in_SpriteClips.h = m_SpriteClips[(int) mCurrentSprite_].h - 10;

    SDL_RenderFillRect(g_Renderer, &m_SpriteClips[(int) mCurrentSprite_]);

    if(check == 1)
        SDL_SetRenderDrawColor(g_Renderer, 255, 105, 180, 128);
    else
        SDL_SetRenderDrawColor(g_Renderer, 192, 192, 192, 255);

    SDL_RenderFillRect(g_Renderer, &in_SpriteClips);

    m_Button[(int) mCurrentSprite_].createTextTexture().render(mPosition_.x + OFFSET, mPosition_.y + OFFSET / 2);

    if(check == 1)
    {
        t_BlackPieces[(int) PieceName::KING].render(mPosition_.x - MENU_HEIGHT ,mPosition_.y, MENU_HEIGHT, MENU_HEIGHT);
        t_BlackPieces[(int) PieceName::KING].render(mPosition_.x + MENU_WIDTH ,mPosition_.y, MENU_HEIGHT, MENU_HEIGHT);
    }
}

void Button::setColor(Color type)
{
    switch (type)
    {
    case Color::BLACK_COLOR:
        //SDL_Color color = {0, 0, 0};
        mTextColor_ = {0, 0, 0};
        break;
    case Color::WHITE_COLOR:
        //SDL_Color color = {255, 255, 255};
        mTextColor_ = {255, 255, 255};
        break;
    case Color::RED_COLOR:
        //SDL_Color color = {255, 0, 0};
        mTextColor_ = {255, 0, 0};
        break;
    case Color::GREEN_COLOR:
        //SDL_Color color = {0, 255, 0};
        mTextColor_ = {0, 255, 0};
        break;
    case Color::BLUE_COLOR:
        //SDL_Color color = {0, 0, 255};
        mTextColor_ = {0, 0, 255};
        break;
    case Color::SILVER_COLOR:
        //SDL_Color color = {192, 192, 192};
        mTextColor_ = {192, 192, 192};
        break;
    case Color::GRAY_COLOR:
        //SDL_Color color = {128, 128, 128};
        mTextColor_ = {128, 128, 128};
        break;
    case Color::DEEPPINK_COLOR:
        //SDL_Color color = {255, 20, 147};
        mTextColor_ = {255, 20, 147};
        break;
    case Color::LIGHTPINK_COLOR:
        //SDL_Color color = {255, 182, 192};
        mTextColor_ = {255, 182, 192};
        break;
    default:
        break;
    }
}
