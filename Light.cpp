#include "Light.h"
#include "Constants.h"
#include "Textures.h"
#include <math.h>
#define PI 3.14159265 // PI

Textures ShadowTexture;
Textures Shadow2Texture;
Textures Shadow3Texture;

Light::Light()
{
	cube[1] = {200,200,200,200};
}

Light::~Light()
{
    //dtor
}

int Light::LoadMedia(SDL_Renderer* Renderer)
{
    //Load PNG Shadow texture
    if((ShadowTexture.LoadFromFile(Renderer, "assets/shadow.png")) == 0)
    {
        cout << "Unable to Load texture image! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    if((Shadow2Texture.LoadFromFile(Renderer, "assets/shadow2.png")) == 0)
    {
        cout << "Unable to Load texture image! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    if((Shadow3Texture.LoadFromFile(Renderer, "assets/shadow3.png")) == 0)
    {
        cout << "Unable to Load texture image! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}


void Light::Render(SDL_Renderer* Renderer, SDL_Rect* camera)
{
}

void Light::Cleanup()
{
    ShadowTexture.Free();
    Shadow2Texture.Free();
    Shadow3Texture.Free();
}
