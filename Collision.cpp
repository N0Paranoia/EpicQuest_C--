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
    i_leftA = a.x;
    i_rightA = a.x + a.w;
    i_topA = a.y;
    i_bottomA = a.y + a.h;

    i_leftB = b.x;
    i_rightB = b.x + b.w;
    i_topB = b.y;
    i_bottomB = b.y + b.h;

    if(i_bottomA <= i_topB)
    {
        return false;
    }
    if(i_topA >= i_bottomB)
    {
        return false;
    }
    if(i_rightA <= i_leftB)
    {
        return false;
    }
    if(i_leftA >= i_rightB)
    {
        return false;
    }
    return true;
}
bool Collision::CheckCloud_Rect(float timeStep, SDL_Rect a, SDL_Rect b)
{
    i_leftA = a.x;
    i_rightA = a.x + a.w;
    i_topA = a.y + a.h - (GRAVITY * timeStep);
    i_bottomA = a.y + a.h;

    i_leftB = b.x;
    i_rightB = b.x + b.w;
    i_topB = b.y;
    i_bottomB = b.y + (GRAVITY * timeStep);

    if(i_bottomA <= i_topB)
    {
        return false;
    }
    if(i_topA >= i_bottomB)
    {
        return false;
    }
    if(i_rightA <= i_leftB)
    {
        return false;
    }
    if(i_leftA >= i_rightB)
    {
        return false;
    }
    return true;
}

bool Collision::Check_Slope_45_Right_Rect(SDL_Rect a, SDL_Rect b)
{
    i_leftA = a.x;
    i_rightA = a.x + a.w;
    i_topA = a.y;
    i_bottomA = a.y + a.h;

    i_leftB = b.x;
    i_rightB = b.x + b.w;
    i_topB = b.y;
    i_bottomB = b.y + b.h;
    //[\]
    if(i_bottomA <= (i_leftA % TILE_SIZE) + i_topB)
    {
    return false;
    }
    if(i_topA >= i_bottomB)
    {
        return false;
    }
    if(i_rightA <= i_leftB)
    {
        return false;
    }
    if(i_leftA >= i_rightB)
    {
        return false;
    }
    return true;
}

bool Collision::Check_Slope_45_Left_Rect(SDL_Rect a, SDL_Rect b)
{
    i_leftA = a.x;
    i_rightA = a.x + a.w; // The -1 counters that the "(i_rightA % TILE_SIZE)" outcom is 0.
    i_topA = a.y;
    i_bottomA = a.y + a.h;

    i_leftB = b.x;
    i_rightB = b.x + b.w;
    i_topB = b.y;
    i_bottomB = b.y + b.h;
    //[/]
        if(i_bottomA <= (TILE_SIZE - (i_rightA % TILE_SIZE) + i_topB))
        {
            return false;
        }
    if(i_topA >= i_bottomB)
    {
        return false;
    }
    if(i_rightA <= i_leftB)
    {
        return false;
    }
    if(i_leftA >= i_rightB)
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
bool Collision::Cloud_Rect(float timeStep, SDL_Rect cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_LADDER_TOP || tiles[i]->getType() == TILE_PLATFORM)
        {
            if(this->CheckCloud_Rect(timeStep, cBox, tiles[i]->getTileBox()))
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
bool Collision::Stick_Rect(float timeStep, SDL_Rect cBox, Tile* tiles[])
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
            if(this->CheckCloud_Rect(timeStep, cBox, tiles[i]->getTileBox()))
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
    f_leftA = a.x;
    f_rightA = a.x + a.w;
    f_topA = a.y;
    f_bottomA = a.y + a.h;

    f_leftB = b.x;
    f_rightB = b.x + b.w;
    f_topB = b.y;
    f_bottomB = b.y + b.h;

    if(f_bottomA <= f_topB)
    {
        return false;
    }
    if(f_topA >= f_bottomB)
    {
        return false;
    }
    if(f_rightA <= f_leftB)
    {
        return false;
    }
    if(f_leftA >= f_rightB)
    {
        return false;
    }
    return true;
}

bool Collision::CheckCloud_Box(float timeStep, Box a, SDL_Rect b)
{
    f_leftA = a.x;
    f_rightA = a.x + a.w;
    f_topA = a.y + a.h - (GRAVITY * timeStep);
    f_bottomA = a.y + a.h;

    f_leftB = b.x;
    f_rightB = b.x + b.w;
    f_topB = b.y;
    f_bottomB = b.y + (GRAVITY * timeStep);

    if(f_bottomA <= f_topB)
    {
        return false;
    }
    if(f_topA >= f_bottomB)
    {
        return false;
    }
    if(f_rightA <= f_leftB)
    {
        return false;
    }
    if(f_leftA >= f_rightB)
    {
        return false;
    }
    return true;
}

bool Collision::Check_Slope_45_Right_Box(Box a, SDL_Rect b)
{
    i_leftA = a.x;
    i_rightA = a.x + a.w;
    i_topA = a.y;
    i_bottomA = a.y + a.h;

    i_leftB = b.x;
    i_rightB = b.x + b.w;
    i_topB = b.y;
    i_bottomB = b.y + b.h;
    //[\]
    if(i_bottomA <= (i_leftA % TILE_SIZE) + i_topB)
    {
        return false;
    }
    if(i_topA >= i_bottomB)
    {
        return false;
    }
    if(i_rightA <= i_leftB)
    {
        return false;
    }
    if(i_leftA >= i_rightB)
    {
        return false;
    }
    return true;
}

bool Collision::Check_Slope_45_Left_Box(Box a, SDL_Rect b)
{
    i_leftA = a.x;
    i_rightA = a.x + (a.w-1); // The -1 counters that the "(i_rightA % TILE_SIZE)" outcom is 0.
    i_topA = a.y;
    i_bottomA = a.y + a.h;

    i_leftB = b.x;
    i_rightB = b.x + b.w;
    i_topB = b.y;
    i_bottomB = b.y + b.h;
    //[/]
    if(i_bottomA <= (TILE_SIZE - (i_rightA % TILE_SIZE) + i_topB))
    {
        return false;
    }
    if(i_topA >= i_bottomB)
    {
        return false;
    }
    if(i_rightA <= i_leftB)
    {
        return false;
    }
    if(i_leftA >= i_rightB)
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
                // cout << "collission = Var_Box" << endl;
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
                // cout << "collission = Wall_Box" << endl;
                return true;
            }
        }
    }
    return false;
}

bool Collision::Cloud_Box(float timeStep, Box cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_LADDER_TOP || tiles[i]->getType() == TILE_PLATFORM)
        {
            if(this->CheckCloud_Box(timeStep, cBox, tiles[i]->getTileBox()))
            {
                // cout << "collission = Cloud_Box" << endl;
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
                // cout << "collission = Slope_45_Right_Box" << endl;
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
                // cout << "collission = Slope_45_Left_Box" << endl;
                return true;
            }
        }
    }
    return false;
}

