#include "EQ.h"

bool EQ::LoadMedia()
{
    //Load PNG texture
	if((Texture = loadTexture("background.png")) == NULL)
	{
		cout << "Unables to Load texture image! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}

	return true;
}
