#include "World.h"
#include "Constants.h"
#include "Texture.h"
#include "Tile.h"
#include <fstream>

//Texture playerTexture;
Texture TileSheetTexture;

World::World()
{

}

World::~World()
{
    //dtor
}

int World::Init(int x, int y, int TileType)
{

}


int World::LoadMedia(SDL_Renderer* Renderer, Tile* tiles[])
{
    //Load Tilemap
    if(!SetTiles(tiles))
    {
        cout << "Unable to load Tile Map! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    //Load Player spritesheet
    if((TileSheetTexture.LoadFromFile(Renderer, "assets/tileSheet48.png")) == NULL)
    {
        cout << "Unable to load Tile Texture! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        //All tile textures
        TileClips[CLEAR].x = -TILE_SIZE;
        TileClips[CLEAR].y = -TILE_SIZE;
        TileClips[CLEAR].w = TILE_SIZE;
        TileClips[CLEAR].h = TILE_SIZE;

        TileClips[SKY].x = 0 * TILE_SIZE;
        TileClips[SKY].y = 0 * TILE_SIZE;
        TileClips[SKY].w = TILE_SIZE;
        TileClips[SKY].h = TILE_SIZE;

        TileClips[WALL].x = 1 * TILE_SIZE;
        TileClips[WALL].y = 0 * TILE_SIZE;
        TileClips[WALL].w = TILE_SIZE;
        TileClips[WALL].h = TILE_SIZE;

        TileClips[WOOD].x = 2 * TILE_SIZE;
        TileClips[WOOD].y = 0 * TILE_SIZE;
        TileClips[WOOD].w = TILE_SIZE;
        TileClips[WOOD].h = TILE_SIZE;

        TileClips[DOOR].x = 3 * TILE_SIZE;
        TileClips[DOOR].y = 0 * TILE_SIZE;
        TileClips[DOOR].w = TILE_SIZE;
        TileClips[DOOR].h = TILE_SIZE;

        TileClips[LAVA].x = 0 * TILE_SIZE;
        TileClips[LAVA].y = 1 * TILE_SIZE;
        TileClips[LAVA].w = TILE_SIZE;
        TileClips[LAVA].h = TILE_SIZE;

        TileClips[GRASS].x = 1 * TILE_SIZE;
        TileClips[GRASS].y = 1 * TILE_SIZE;
        TileClips[GRASS].w = TILE_SIZE;
        TileClips[GRASS].h = TILE_SIZE;

        TileClips[WATER].x = 2 * TILE_SIZE;
        TileClips[WATER].y = 1 * TILE_SIZE;
        TileClips[WATER].w = TILE_SIZE;
        TileClips[WATER].h = TILE_SIZE;

        TileClips[PLATFORM].x = 2 * TILE_SIZE;
        TileClips[PLATFORM].y = 2 * TILE_SIZE;
        TileClips[PLATFORM].w = TILE_SIZE;
        TileClips[PLATFORM].h = TILE_SIZE;

        TileClips[LADDER].x = 3 * TILE_SIZE;
        TileClips[LADDER].y = 2 * TILE_SIZE;
        TileClips[LADDER].w = TILE_SIZE;
        TileClips[LADDER].h = TILE_SIZE;

        TileClips[LADDER_TOP].x = 4 * TILE_SIZE;
        TileClips[LADDER_TOP].y = 2 * TILE_SIZE;
        TileClips[LADDER_TOP].w = TILE_SIZE;
        TileClips[LADDER_TOP].h = TILE_SIZE;

        TileClips[SLOPE_RIGHT].x = 0 * TILE_SIZE;
        TileClips[SLOPE_RIGHT].y = 3 * TILE_SIZE;
        TileClips[SLOPE_RIGHT].w = TILE_SIZE;
        TileClips[SLOPE_RIGHT].h = TILE_SIZE;

        TileClips[SLOPE_LEFT].x = 1 * TILE_SIZE;
        TileClips[SLOPE_LEFT].y = 3 * TILE_SIZE;
        TileClips[SLOPE_LEFT].w = TILE_SIZE;
        TileClips[SLOPE_LEFT].h = TILE_SIZE;
    }
}

bool World::SetTiles(Tile* tiles[])
{
    int x = 0;
    int y = 0;

    std::ifstream map("assets/level.map");

    if (map == NULL)
    {
        cout << "Unable to load Tile Map file!" << endl;
        return false;
    }
    else
    {
        //Initialize tiles
        for(int i = 0; i < TOTAL_TILES; i++)
        {
            int Type = -1;

            map >> Type;

            if(map.fail())
            {
                cout << "Error loading map: Unexpected end of file!" << endl;
                return false;
                break;
            }
            //if number is valid tile number
            if((Type >= 0) && (Type < TOTAL_TILE_SPRITES))
            {
                tiles[i] = new Tile(x, y, Type);
            }
            else
            {
               cout << "Error loading map: Invalid tile type!" << endl;
               return false;
               break;
            }
            x += TILE_SIZE;
			//If we've gone too far
			if(x >= LEVEL_WIDTH)
			{
                //Move back
				x = 0;
				//Move to the next row
				y += TILE_SIZE;
			}
        }

    }
    return true;
}

void World::Render(SDL_Renderer* Renderer, SDL_Rect* camera, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILE_SPRITES; i++)
    {
//        TileSheetTexture.Render(Renderer, tiles.TileBox->x - camera->x, i*TILE_SIZE - camera->y, &TileClips[i]);
        TileSheetTexture.Render(Renderer, i*TILE_SIZE - camera->x, i*TILE_SIZE - camera->y, &TileClips[i]);
    }

}
