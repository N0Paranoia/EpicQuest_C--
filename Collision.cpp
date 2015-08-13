#include "Collision.h"
#include "Constants.h"

Collision::Collision()
{
    //ctor
}

Collision::~Collision()
{
    //dtor
}

// SDL_Rect collisions (ints)
bool Collision::Check_Rect(SDL_Rect a, SDL_Rect b)
{
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if(bottomA <= topB)
    {
        return false;
    }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}
bool Collision::CheckCloud_Rect(SDL_Rect a, SDL_Rect b)
{
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y + a.h - GRAVITY;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + GRAVITY;

    if(bottomA <= topB)
    {
        return false;
    }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool Collision::Check_Slope_45_Right_Rect(SDL_Rect a, SDL_Rect b)
{
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //[\]
        if(bottomA <= (leftA % TILE_SIZE) + topB)
        {
        return false;
        }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool Collision::Check_Slope_45_Left_Rect(SDL_Rect a, SDL_Rect b)
{
    leftA = a.x;
    rightA = a.x + (a.w-1); // The -1 counters that the "(rightA % TILE_SIZE)" outcom is 0.
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //[/]
        if(bottomA <= (TILE_SIZE - (rightA % TILE_SIZE) + topB))
        {
            return false;
        }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
            return false;
    }
    return true;
}

bool Collision::Var_Rect(SDL_Rect cBox, Tile* tiles[], int type)
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == type)
        {
            if(this->Check_Rect(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}
bool Collision::Wall_Rect(SDL_Rect cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_WALL)
        {
            if(this->Check_Rect(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}
bool Collision::Cloud_Rect(SDL_Rect cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_LADDER_TOP || tiles[i]->getType() == TILE_PLATFORM)
        {
            if(this->CheckCloud_Rect(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}
bool Collision::Slope_45_Right_Rect(SDL_Rect cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_SLOPE_RIGHT)
        {
            if(this->Check_Slope_45_Right_Rect(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::Slope_45_Left_Rect(SDL_Rect cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_SLOPE_LEFT)
        {
            if(this->Check_Slope_45_Left_Rect(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}
bool Collision::Stick_Rect(SDL_Rect cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        // Stick Collision for all "Solid" tiles
        if(tiles[i]->getType() == TILE_WALL) 
        {
            if(this->Check_Rect(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
        // Stick Collision for all "Cloud" tiles
        else if(tiles[i]->getType() == TILE_PLATFORM ||
            tiles[i]->getType() == TILE_LADDER_TOP) 
        {
            if(this->CheckCloud_Rect(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
        // Stick Collision for all "45° left Slope" tiles [/]
        else if(tiles[i]->getType() == TILE_SLOPE_LEFT)
        {
            if(this->Check_Slope_45_Left_Rect(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
        //Stick Collision for all "45° right Slope" tiles [\] 
        else if(tiles[i]->getType() == TILE_SLOPE_RIGHT)
        {
            if(this->Check_Slope_45_Right_Rect(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }   
    }
    return false;
}

// Box Collisions (floats)
bool Collision::Check_Box(Box a, SDL_Rect b)
{
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if(bottomA <= topB)
    {
        return false;
    }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool Collision::CheckCloud_Box(Box a, SDL_Rect b)
{
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y + a.h - GRAVITY;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + GRAVITY;

    if(bottomA <= topB)
    {
        return false;
    }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool Collision::Check_Slope_45_Right_Box(Box a, SDL_Rect b)
{
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //[\]
        if(bottomA <= (leftA % TILE_SIZE) + topB)
        {
        return false;
        }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool Collision::Check_Slope_45_Left_Box(Box a, SDL_Rect b)
{
    leftA = a.x;
    rightA = a.x + (a.w-1); // The -1 counters that the "(rightA % TILE_SIZE)" outcom is 0.
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //[/]
        if(bottomA <= (TILE_SIZE - (rightA % TILE_SIZE) + topB))
        {
            return false;
        }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
            return false;
    }
    return true;
}

bool Collision::Var_Box(Box cBox, Tile* tiles[], int type)
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == type)
        {
            if(this->Check_Box(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::Wall_Box(Box cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_WALL)
        {
            if(this->Check_Box(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::Cloud_Box(Box cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_LADDER_TOP || tiles[i]->getType() == TILE_PLATFORM)
        {
            if(this->CheckCloud_Box(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::Slope_45_Right_Box(Box cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_SLOPE_RIGHT)
        {
            if(this->Check_Slope_45_Right_Box(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::Slope_45_Left_Box(Box cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_SLOPE_LEFT)
        {
            if(this->Check_Slope_45_Left_Box(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

