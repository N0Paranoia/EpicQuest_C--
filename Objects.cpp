#include "Objects.h"
#include "Constants.h"
#include "Textures.h"

Objects::Objects(int x, int y, int Type) {
    ObjectBox.x = x;
    ObjectBox.y = y;
    ObjectBox.w = TILE_SIZE;
    ObjectBox.h = TILE_SIZE;

    ObjectType = Type;
}

void Objects::Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera) {
    //  textures->Render(Renderer, ObjectBox.x - camera->x, ObjectBox.y - camera->y, &clips[1]);
}

