#include "Light.h"
#include "Constants.h"

Light::Light(int x, int y)
{
	ShadowBox.x = x;
	ShadowBox.y = y;
}

Light::~Light() 
{
    //dtor
}

void Light::Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera)
{
}

void Light::Cleanup()
{
}
