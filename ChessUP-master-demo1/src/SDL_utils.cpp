#include "../include/common.h"
#include "../include/SDL_utils.h"

void logSDLError(std::ostream& os, const std::string &msg, int error_code, bool fatal)
{
    if (error_code == SDL_ERROR)
		os << msg << " Error: " << SDL_GetError() << std::endl;

	if (error_code == IMG_ERROR)
		os << msg << " Error: " << IMG_GetError() << std::endl;

	if (error_code == MIX_ERROR)
		os << msg << " Error: " << Mix_GetError() << std::endl;

	if (error_code == TTF_ERROR)
		os << msg << " Error: " << TTF_GetError() << std::endl;

    if (fatal) {
        //SDL_Quit();
        //exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight, const char* windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", SDL_ERROR, true);
#ifndef LAB
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
#else
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
#endif // LAB

    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", SDL_ERROR, true);

#ifndef LAB
    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#else
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
#endif // LAB

    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", SDL_ERROR, true);
    else
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
            logSDLError(std::cout, "SDL_image could not initialize!", IMG_ERROR, true);

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            logSDLError(std::cout, "SDL_mixer could not initialize!", MIX_ERROR, true);

        if (TTF_Init() == -1)
            logSDLError(std::cout, "SDL_ttf could not initialize!", TTF_ERROR, true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void updateScreen(SDL_Window* window, SDL_Renderer* renderer)
{
#ifndef LAB
    SDL_RenderPresent(renderer);
#else
    SDL_UpdateWindowSurface(window);
#endif // LAB
}
