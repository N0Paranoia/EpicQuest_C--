#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL.h>
#include "Constants.h"
#include "Textures.h"

class Objects {
public:
	Objects(int x, int y, int Type);
	~Objects();
	int getType();
	SDL_Rect getObjectBox();
	void Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera);
  
protected:

private:
	int ObjectType;
	SDL_Rect ObjectBox;
    SDL_Rect Dagger;
};

#endif // OBJECTS_H
