#ifndef EQ_H
#define EQ_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

std::stringstream timeText;
std::stringstream debugText;

class EQ {
private:
    bool Running;
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Texture* Texture;
    TTF_Font* Font;
    SDL_Color textColor;
    int countedFrames;

    float avgFPS;
    float timeStep;
    int frameTicks;

    int xMouse;
    int yMouse;

public:
    EQ();
    int Execute();

public:
    void Event(SDL_Event* Event);
    void Fps();
    void FpsCap();
    bool Init();
    bool LoadMedia();
    bool InitKeys();
    //Loads individual image as texture
    SDL_Texture* loadTexture(std::string path);
    void Input();
    void Loop();
    void Render();
    void Cleanup();
    void Debug();

    void Lighting();
};

#endif // EQ_H
