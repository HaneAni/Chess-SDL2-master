#include "../include/Texture.h"

Texture::Texture()
{
    // Initialize
    mTexture_ = nullptr;
    mWidth_ = 0;
    mHeight_ = 0;
}

Texture::~Texture()
{
    // Deallocate
    freeTexture();
}

bool Texture::loadFromFile(const std::string &file)
{
    // Get rid of preexisting texture
    freeTexture();

    // The final texture
	SDL_Texture *newTexture = nullptr;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(file.c_str());
    if (loadedSurface == nullptr)
        logSDLError(std::cout, "Load Image", IMG_ERROR, true);
	else
    {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_FALSE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(g_Renderer, loadedSurface);
		if (newTexture == nullptr)
			logSDLError(std::cout, "Create Texture From Surface", IMG_ERROR, true);
        else
        {
            // Get image dimensions
            mWidth_ = loadedSurface->w;
            mHeight_ = loadedSurface->h;
        }

        // Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture_ = newTexture;
	return mTexture_ != nullptr;
}

bool Texture::loadFromRenderedText(const std::string text, SDL_Color color, TTF_Font* font)
{
    //Get rid of preexisting texture
    freeTexture();

    // The final texture
	SDL_Texture *newTexture = nullptr;

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if(textSurface == nullptr)
        logSDLError(std::cout, "Render Font", TTF_ERROR, true);
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(g_Renderer, textSurface);
        if(newTexture == nullptr)
            logSDLError(std::cout, "Create Texture From Surface", TTF_ERROR, true);
        else
        {
            //Get image dimensions
            mWidth_ = textSurface->w;
            mHeight_ = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    mTexture_ = newTexture;
    return mTexture_ != nullptr;
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    // Set rendering space
    SDL_Rect renderQuad = {x, y, mWidth_, mHeight_};

    // Set clip rendering dimensions
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render texture to screen
    SDL_RenderCopyEx(g_Renderer, mTexture_, clip, &renderQuad, angle, center, flip);
}

void Texture::render(int x, int y, int w, int h)
{
    // Set rendering space
    SDL_Rect renderQuad = {x, y, w, h};
    // Render texture to screen
    SDL_RenderCopy(g_Renderer, mTexture_, NULL, &renderQuad);
}

void Texture::renderBackground()
{
    int w = mWidth_;
    int h = mHeight_;

    if ((w * SCREEN_HEIGHT) > (SCREEN_WIDTH * h))
    {
        w = SCREEN_HEIGHT * w / h;
        h = SCREEN_HEIGHT;
    }
    else
    {
        h = SCREEN_WIDTH * h / w;
        w = SCREEN_WIDTH;
    }
    render((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2, w, h);
}

void Texture::freeTexture()
{
    if(mTexture_ != nullptr)
    {
        SDL_DestroyTexture(mTexture_);
        mTexture_ = nullptr;
        mWidth_ = 0;
        mHeight_ = 0;
    }
}
