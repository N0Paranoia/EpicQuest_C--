#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include "Constants.h"

using namespace std;

class Camera
{
    public:
        SDL_Rect cameraRect;
        SDL_Rect centerRect;
        SDL_Rect test;
    public:
        Camera();
        virtual ~Camera();
        void Center(Box* playerRect);
        void Follow();
        void Update(Box* playerRect);
        void Render(SDL_Renderer* Renderer);
    protected:
    private:
};

#endif // CAMERA_H
