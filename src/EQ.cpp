#include "EQ.h"
#include "Timer.h"
#include "Player.h"
#include "Textures.h"
#include "Camera.h"
#include "World.h"
#include "Constants.h"

Timer timer;
Player player;
World world;
Camera camera;
Textures wallpaperTexture;
Tile* tileSet[TOTAL_TILES];

EQ::EQ()
{
    Running = true;
    Window = nullptr;
    Renderer = nullptr;
    Texture = nullptr;
    Font = nullptr;

    countedFrames  = 0;
}

bool EQ::Init()
{
    timer.Start();
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

    if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED/* | SDL_RENDERER_PRESENTVSYNC*/)) == NULL)
    {
        cout << "Unable to create Renderer! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    // initialize image loading for PNG
    if(!(IMG_Init(IMG_INIT_PNG)& IMG_INIT_PNG))
    {
        cout << "Unable to initialize SDL_Image! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

bool EQ::LoadMedia()
{
//    Tile* tileSet[TOTAL_TILES];
    //The level tiles
    //Load Player texture
    if((player.LoadMedia(Renderer)) == NULL)
    {
        return false;
    }
    //Load Tile Sheet
    if((world.LoadMedia(Renderer, tileSet)) == NULL)
    {
        return false;
    }
    //Load PNG background texture
    if((wallpaperTexture.LoadFromFile(Renderer, "assets/background.png")) == NULL)
	{
		cout << "Unable to Load texture image! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
    return true;
}

void EQ::Event(SDL_Event* event)
{
    if(event->type == SDL_QUIT)
    {
        Running = false;
    }
    else if(event->type == SDL_KEYDOWN)
    {
        switch(event->key.keysym.sym)
        {
        case SDLK_q:
            Running = false;
            cout << "Quit by keyboard(q)" << endl;
            break;
        case SDLK_o:
            if(timer.isStarted())
            {
                timer.Stop();
            }
            else
            {
                timer.Start();
            }
            break;
        case SDLK_p:
            if(timer.isPaused())
            {
                timer.Unpause();
            }
            else
            {
                timer.Pause();
            }
        }
    }
}

void EQ::Input()
{
     player.Input(tileSet);
}

void EQ::Loop()
{
    camera.Center(&player.playerRect);
    float avgFPS = countedFrames / (timer.getTicks() / 1000.f);
    if(avgFPS > 2000000)
    {
        avgFPS = 0;
    }
    cout << avgFPS << endl;
}

void EQ::Render()
{
    //Set Default colors
    SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //Clear screen
    SDL_RenderClear(Renderer);
    //Render Texture to screen
    wallpaperTexture.Render(Renderer, 0, 0);
    // Render Tiles
    world.Render(Renderer, &camera.cameraRect, tileSet);
    // Render Player data
    player.Render(Renderer, &camera.cameraRect);
    //Render Camara outline
    camera.Render(Renderer);
    //Update screen
    SDL_RenderPresent(Renderer);

    ++countedFrames;
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

    if(this->Init() == false)
    {
        return -1;
    }
    if(this->LoadMedia() == false)
    {
        return -1;
    }
    SDL_Event event;

    while(Running)
    {
        while(SDL_PollEvent(&event))
        {
           this->Event(&event);
        }
        this->Input();
        this->Loop();
        this->Render();
    }
    this->Cleanup();
    return 0;
}


int main(int argc, char* argv[])
{
    EQ EpicQuest;
    return EpicQuest.Execute();
}
