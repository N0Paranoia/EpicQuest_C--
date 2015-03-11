#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>

using namespace std;

class Texture
{
    public:
        Texture();
        virtual ~Texture();
        bool LoadFromFile(SDL_Renderer* Renderer, std::string path);
        void Free();
        void Render(SDL_Renderer* Renderer, int x, int y);
        int getWidth();
        int getHeight();
    protected:
    private:
        //Actual hardware texture
        SDL_Texture* texture;
        //image dimensions
        int mWidth;
        int mHeight;
};

#endif // TEXTURE_H
