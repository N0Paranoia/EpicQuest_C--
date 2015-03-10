#include "EQ.h"
#include "Constants.h"

bool EQ::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    if((Window = SDL_CreateWindow("EpicQuest",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    {
        cout << "Unable to create SDL_Window! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
    {
        cout << "Unable to create Renderer! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    // initialize image loading for PNG
    if(!(IMG_Init(IMG_INIT_PNG)& IMG_INIT_PNG))
    {
        cout << "Unables to initialize SDL_Image! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

SDL_Texture* EQ::loadTexture(std::string path)
{

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        cout << "Unable to load image! SDL_Error: " << path.c_str() << IMG_GetError() << endl;
    }

    //Create texture from surface pixels
    if((newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface)) == NULL)
    {
        cout << "Unable to create texture! SDL_Error: " << path.c_str() << SDL_GetError() << endl;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface );

    return newTexture;
}
