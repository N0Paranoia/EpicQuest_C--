#include "Camera.h"
#include "Constants.h"
#include <iostream>

Camera::Camera()
{
    center.x = 0;
    center.y = 0;
    center.w = 2*TILE_SIZE;
    center.h = 4*TILE_SIZE;

    camera.x = 0;
    camera.y = 0;
    camera.w = WINDOW_WIDTH;
    camera.h = WINDOW_HEIGHT;

    test = {0,0,WINDOW_WIDTH, WINDOW_HEIGHT};
}

Camera::~Camera()
{
    //dtor
}

void Camera::Center(SDL_Rect* playerRect)
{
    if(center.x > playerRect->x - camera.x)
    {
        center.x = playerRect->x - camera.x;
    }
    if((center.x + center.w) < (playerRect->x + playerRect->w) - camera.x)
    {
        center.x = (playerRect->x + playerRect->w) - center.w - camera.x;
    }
    if(center.y > playerRect->y - camera.y)
    {
        center.y = playerRect->y - camera.y;
    }
    if((center.y + center.h) < (playerRect->y + playerRect->h) - camera.y)
    {
        center.y = (playerRect->y + playerRect->h) - center.h - camera.y;
    }
    this->Follow();
}

void Camera::Follow()
{
    camera.x = (center.x + center.w/2) - WINDOW_WIDTH/2;
    camera.y = (center.y + center.h/2) - WINDOW_HEIGHT/2;

    if(camera.x < 0)
    {
        camera.x = 0;
    }
    if(camera.y < 0)
    {
        camera.y = 0;
    }
    if((camera.x + camera.w) > (LEVEL_WIDTH*TILE_SIZE))
    {
        camera.x = LEVEL_WIDTH*TILE_SIZE - camera.w;
    }
    if((camera.y + camera.h) > (LEVEL_HEIGHT*TILE_SIZE))
    {
        camera.y = LEVEL_HEIGHT*TILE_SIZE - camera.h;
    }
}


void Camera::Render(SDL_Renderer* Renderer)
{
    cout << camera.x + camera.w << endl;
    SDL_SetRenderDrawColor(Renderer, 0x00, 0xff, 0x00, 0xff);
    SDL_RenderDrawRect(Renderer, &camera);
    SDL_RenderDrawRect(Renderer, &center);
    SDL_RenderDrawRect(Renderer, &test);
}
