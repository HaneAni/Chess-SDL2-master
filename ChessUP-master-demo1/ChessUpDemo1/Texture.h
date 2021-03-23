#ifndef SDL_INCLUDES
#define SDL_INCLUDES

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif // SDL_INCLUDES

#include "SDL_utils.h"
#include "common.h"

#ifndef TEXTURE_H
#define TEXTURE_H


class Texture
{
public:
    // Initializes variables
    Texture();

    // Deallocates memory
    ~Texture();

    // Loads images from a file
    bool loadFromFile(const std::string &file);

    // Renders texture on screen
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void render(int x, int y, int w, int h);
    void renderBackground();

    // Deallocates texture
    void freeTexture();

    // Gets image dimensions
    int getWidth() { return mWidth_; }
    int getHeight() { return mHeight_; }

private:
    // The actual hardware texture
    SDL_Texture* mTexture_;

    // Image dimensions
    int mWidth_;
    int mHeight_;

};


#endif // TEXTURE_H
