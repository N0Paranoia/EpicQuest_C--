#include "EQ.h"
#include "Player.h"
#include "Constants.h"

Player player;

EQ::EQ()
{

}

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

bool EQ::LoadMedia()
{
    //Load PNG texture
	if((Texture = loadTexture("background.png")) == NULL)
	{
		cout << "Unables to Load texture image! SDL_Error: " << SDL_GetError() << endl;
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

void EQ::Event(SDL_Event* Event)
{
    if(Event->type == SDL_QUIT)
    {
        Running = false;
    }
    else if(Event->type == SDL_KEYDOWN)
    {
        //Define Keyboard inputs
        switch(Event->key.keysym.sym)
        {
        case SDLK_q:
            cout << "Quit" << endl;
            Running = false;
            break;
        case SDLK_a:
            cout << "Left" << endl;
            break;
        case SDLK_d:
            cout << "Right" << endl;
            break;
        case SDLK_w:
            cout << "Up" << endl;
            break;
        case SDLK_s:
            cout << "Down" << endl;
            break;
        case SDLK_SPACE:
            cout << "Jump" << endl;
            break;
        }
    }
}

void EQ::Loop()
{

}

void EQ::Render()
{
    //Set Default color
    SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    //Clear screen
    SDL_RenderClear( Renderer );
    //Render Texture to screen
    SDL_RenderCopy(Renderer, Texture, NULL, NULL);

    //Render red filled quad
    SDL_Rect fillRect = { WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
    SDL_SetRenderDrawColor( Renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( Renderer, &fillRect );

    //Update screen
    SDL_RenderPresent( Renderer );
}

void EQ::Cleanup()
{
    if(Renderer)
    {
        SDL_DestroyRenderer(Renderer);
        Renderer = nullptr;
    }
    if(Texture)
    {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }
    if(Window)
    {
        SDL_DestroyWindow(Window);
        Window = nullptr;
    }


    SDL_Quit();
}

int EQ::Execute()
{
    if(Init() == false)
    {
        return -1;
    }
    if(LoadMedia() == false)
    {
        return -1;
    }
    SDL_Event event;

    while(Running)
    {
        while(SDL_PollEvent(&event))
        {
            Event(&event);
        }
        Loop();
        Render();
    }
    Cleanup();
    return 0;
}


int main(int argc, char* argv[])
{
    EQ EpicQuest;
    return EpicQuest.Execute();
}
