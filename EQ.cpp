#include <fstream>
#include "EQ.h"
#include "Physics.h"
#include "Timer.h"
#include "Player.h"
#include "Collision.h"
#include "Mobs.h"
#include "Textures.h"
#include "Camera.h"
#include "World.h"
#include "Constants.h"
#include "Ai.h"

Ai ai;
Timer FPStimer;
Timer CAPtimer;
Physics physics;
Collision collision;
Player player;
Mobs* mobs[TOTAL_TILES];
World world;
Camera camera;
Tile* tileSet[TOTAL_TILES];

Textures wallpaperTexture;
Textures TextTexture;
Textures DebugTexture;

EQ::EQ() {
    Running = true;
    Window = nullptr;
    Renderer = nullptr;

    Texture = nullptr;

    textColor = {0xff,0x00,0x00, 0x00};
    countedFrames  = 0;
}

bool EQ::Init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    if((Window = SDL_CreateWindow("EpicQuest",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)) == NULL) {
        cout << "Unable to create SDL_Window! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/)) == NULL) {
        cout << "Unable to create Renderer! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    // initialize image loading for PNG
    if(!(IMG_Init(IMG_INIT_PNG)& IMG_INIT_PNG)) {
        cout << "Unable to initialize SDL_Image! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    if(TTF_Init() == -1) {
        cout << "Unable to initialize SDL_TTF! SDL_Error: " << TTF_GetError() << endl;
        return false;
    }
    return true;
}

bool EQ::LoadMedia() {
    //Load Player texture
    if((player.LoadMedia(Renderer)) == 0) {
        return false;
    }
    //Load Tile Sheet
    if((world.LoadMedia(Renderer, tileSet, mobs)) == 0) {
        return false;
    }
    //Load PNG background texture
    if((wallpaperTexture.LoadFromFile(Renderer, "assets/background.png")) == 0) {
        cout << "Unable to Load texture image! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    Font = TTF_OpenFont("assets/FreePixel.ttf", 14);
    if(Font == NULL) {
        cout << "Unable to Load font! SDL_Error: " << TTF_GetError() << endl;
        return false;
    }
    return true;
}

void EQ::Event(SDL_Event* event) {
    if(event->type == SDL_QUIT) {
        Running = false;
    } else if(event->type == SDL_KEYDOWN) {
        switch(event->key.keysym.sym) {
        case SDLK_ESCAPE:
            Running = false;
            cout << "Quit by keyboard(Esc)" << endl;
            break;
        // Key For debug purpose
        case SDLK_BACKQUOTE:
            ai.Debug();
            break;
        }
    }
    SDL_GetMouseState(&xMouse,&yMouse);// mouse location
}

void EQ::Fps() {
    // Calculate FPS
    avgFPS = countedFrames / (FPStimer.getTicks() / 1000.f);

    if(avgFPS > 2000000) {
        avgFPS = 0;
    }

    timeText.str("");
    timeText << avgFPS;
    if(!TextTexture.LoadFromRenderedText(Renderer, Font, timeText.str().c_str(), textColor)) {
        cout << "Failed to render text texture!" << endl;
    }
}

void EQ::FpsCap() {
    frameTicks = CAPtimer.getTicks();
    if(frameTicks < TICK_PER_FRAME) {
        SDL_Delay( TICK_PER_FRAME - frameTicks);
    }
}

void EQ::Input() {
    player.Input(tileSet);
}

void EQ::Loop() {
    camera.Center(&player.playerRect);
    player.Update(mobs);
    player.Falling(tileSet);
    world.UpdateMobs(mobs, tileSet, &player.playerRect, &player.SwordBox, &player.ShieldBox);
    // FPStimer.Start();
}

void EQ::Render() {
    //Set Default colors
    SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //Clear screen
    SDL_RenderClear(Renderer);
    //Render Texture to screen
    wallpaperTexture.Render(Renderer, 0, 0);
    // Render Tiles
    world.Render(Renderer, &camera.cameraRect, tileSet, mobs, &player.playerRect, &player.SwordBox);
    //Render Camara outline
    camera.Render(Renderer);
    // Render Player data
    player.Render(Renderer, &camera.cameraRect);
    //Render FPS text
    TextTexture.Render(Renderer, WINDOW_WIDTH - TILE_SIZE, 0);
    //Render Debug text
    DebugTexture.Render(Renderer, 3*TILE_SIZE, 0);
    //Update screen
    SDL_RenderPresent(Renderer);

    // frame counter for FPS
    ++countedFrames;

    this->FpsCap();
}

void EQ::Debug() {
    debugText.str("");
    debugText << "State = " << player._state;
    debugText << "|Xvel = " << player.Xvel;
    debugText << "|Left = " << player.playerRect.x;
    debugText << "|Right = " << player.playerRect.x + player.playerRect.w;
    debugText << "|Top = " << player.playerRect.y;
    debugText << "|Bottom = " << player.playerRect.y + player.playerRect.h;
    debugText << "|left on tile = " << player.playerRect.x % TILE_SIZE;
    debugText << "|right on tile = " << (player.playerRect.x + player.playerRect.w) % TILE_SIZE;

    if(!DebugTexture.LoadFromRenderedText(Renderer, Font, debugText.str().c_str(), textColor)) {
        cout << "Failed to render text texture!" << endl;
    }
}

void EQ::Cleanup() {
    if(Renderer) {
        SDL_DestroyRenderer(Renderer);
        Renderer = nullptr;
    }
    if(Texture) {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }
    if(Window) {
        SDL_DestroyWindow(Window);
        Window = nullptr;
    }
    TextTexture.Free();
    TTF_CloseFont(Font);
    Font = nullptr;
    SDL_Quit();
}

int EQ::Execute() {
    if(this->Init() == false) {
        return -1;
    }
    if(this->LoadMedia() == false) {
        return -1;
    }
    SDL_Event event;
    //start FPS timer
    FPStimer.Start();

    while(Running) {
        CAPtimer.Start();
        while(SDL_PollEvent(&event)) {
            this->Event(&event);
        }
        this->Fps();
        this->Input();
        this->Loop();
        this->Render();

        this->Debug();
    }
    this->Cleanup();
    return 0;
}


int main(int argc, char* argv[]) {
    EQ EpicQuest;
    return EpicQuest.Execute();
}
