#include "Camera.h"
#include "Constants.h"
#include <iostream>

Camera::Camera()
{
    camera.x = 0;
    camera.y = 0;
    camera.w = WINDOW_WIDTH;
    camera.h = WINDOW_HEIGHT;
}

Camera::~Camera()
{
    //dtor
}

void Camera::Follow(SDL_Rect* playerRect)
{
    camera.x = (playerRect->x + playerRect->w/2) - WINDOW_WIDTH/2;
    camera.y = (playerRect->y + playerRect->h/2) - WINDOW_HEIGHT/2;

    if(camera.x < 0)
    {
        camera.x = 0;
    }
    if(camera.x > LEVEL_WIDTH*TILE_SIZE - camera.w)
    {
        camera.x = LEVEL_WIDTH*TILE_SIZE - camera.w;
    }
    if(camera.y < 0)
    {
        camera.y = 0;
    }
    if(camera.y > LEVEL_HEIGHT*TILE_SIZE - camera.h)
    {
        camera.y = LEVEL_HEIGHT*TILE_SIZE - camera.h;
    }
}

void Camera::Render(SDL_Renderer* Renderer)
{
    SDL_SetRenderDrawColor(Renderer, 0x00, 0xff, 0x00, 0xff) ;
    SDL_RenderDrawRect(Renderer, &camera);
}
