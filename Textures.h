#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
#include <iostream>

using namespace std;

class Textures
{
   private:
        //Actual hardware texture
        //image dimensions
        int mWidth;
        int mHeight;
		int radius();
		SDL_Renderer* gRenderer;
		SDL_Texture* texture;
		SDL_Rect textureRect;
		SDL_RendererFlip flip;
		Uint32* myPixels;
	public:        
		Textures();
        virtual ~Textures();
        bool LoadFromFile(SDL_Renderer* Renderer, std::string path);
        bool LoadFromRenderedText(SDL_Renderer* Renderer, TTF_Font* Font, std::string textureText, SDL_Color textColor);
        void Free();
		void Render(SDL_Renderer* Renderer, int x, int y, SDL_Rect* clip = NULL);
        int getWidth();
        int getHeight();
    protected:

};

#endif // TEXTURES_H
