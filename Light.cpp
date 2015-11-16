#include "Light.h"
#include "Constants.h"
#include "Textures.h"

Textures ShadowTexture;
Textures Shadow2Texture;
Textures Shadow3Texture;

Light::Light()
{
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

void Light::InitShadows(int locationX,int locationY)
{
    int draw = 0;
    int x,y;
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        draw += DrawShadows(10,10,cube[i]);
    }
}

int Light::DrawShadows(int locationX,int locationY, SDL_Rect cube)
{
    int x=0,y=0;//location to store the cood to store start location of shadow drawing
	SDL_Rect shadowR = cube;	   //Rect for shadow from start it is the same as the cube Rect
	SDL_Rect shadowR2 = cube;	   //Rect for shadow from start it is the same as the cube Rect
	SDL_Rect cubeR = { 0,0,0,0 };  //Rect for shadow
	bool finish = false;

	int draw = 0;
    return draw;
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
