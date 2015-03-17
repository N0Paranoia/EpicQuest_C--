#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

using namespace std;

class Camera
{
    public:
        SDL_Rect camera;
        SDL_Rect center;
        SDL_Rect test;
    public:
        Camera();
        virtual ~Camera();
        void Center(SDL_Rect* playerRect);
        void Follow();
        void Update(SDL_Rect* playerRect);
        void Render(SDL_Renderer* Renderer);
    protected:
    private:
};

#endif // CAMERA_H
