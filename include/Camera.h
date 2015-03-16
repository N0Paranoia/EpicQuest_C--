#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

using namespace std;

class Camera
{
    public:
        SDL_Rect camera;
    public:
        Camera();
        virtual ~Camera();
        void Follow(SDL_Rect* playerRect);
        int GetCameraX();
        int GetCameraY();
        void Render(SDL_Renderer* Renderer);
    protected:
    private:
};

#endif // CAMERA_H
