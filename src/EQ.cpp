#include "EQ.h"
#include "Player.h"
#include "Texture.h"
#include "Camera.h"
#include "Constants.h"

Player player;
Camera camera;
Texture wallpaperTexture;
//Texture playerTexture;

EQ::EQ()
{
    Running = true;
    Window = nullptr;
    Renderer = nullptr;
    Texture = nullptr;
    PlayerTexture = nullptr;
    Font = nullptr;
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
    //Load Player texture
    if((player.LoadMedia(Renderer)) == NULL)
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
        }
    }
}

void EQ::Input()
{
     player.Input();
}

void EQ::Loop()
{
    camera.Follow(&player.playerRect);
}

void EQ::Render()
{
    //Set Default colors
    SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //Clear screen
    SDL_RenderClear(Renderer);
    //Render Texture to screen
    wallpaperTexture.Render(Renderer, 0, 0);
    // Render Player data
    player.Render(Renderer, &camera.camera);

    //Render Camara outline
    camera.Render(Renderer);

    //Update screen
    SDL_RenderPresent(Renderer);
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
    if(PlayerTexture)
    {
        SDL_DestroyTexture(PlayerTexture);
        PlayerTexture = nullptr;
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
