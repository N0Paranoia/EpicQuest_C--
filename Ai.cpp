#include "Ai.h"
#include "Constants.h"
#include "Collision.h"

Collision aiCollision;

Ai::Ai()
{
    // for(int i = 0; i < TOTAL_TILES; i++)
    // {
    //     Left[i] = true;
    // }
}

Ai::~Ai()
{
    //dtor
}

int Ai::Agro(Mobs* mobs[], int i, Tile* tiles[])
{
    return 0;
}

int Ai::Update(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect)
{
    //----Basic Agro Ai----//
    if(playerRect->x < mobs[i]->getMobBox().x && playerRect->x > mobs[i]->getMobBox().x - AGRO_RANGE)
    {
        Left[i] = true;
        Right[i] = false;
    }
    else if(playerRect->x > mobs[i]->getMobBox().x && playerRect->x < mobs[i]->getMobBox().x + AGRO_RANGE)
    {
        Right[i] = true;
        Left[i] = false;
    }
    else
    {
        Left[i] = false;
        Right[i] = false;
    }
    //----Basic Agro Ai----//

    //----Basic Wallcollision Ai----//
    if(aiCollision.Wall(mobs[i]->getMobBox(), tiles))
    {
        if(Right[i])
        {
            Right[i] = false;
            Left[i] = true;
        }
        else if(Left[i])
        {
            Left[i] = false;
            Right[i] = true;
        }
    }
    //----Basic Wallcollision Ai----//

    //----Basic Movement Ai----//
    if(Right[i])
    {
        return mobs[i]->getMobBox().x +4;
    }
    else if(Left[i])
    {
        return mobs[i]->getMobBox().x -4;
    }
    else
    {
        return mobs[i]->getMobBox().x;
    }
    //----Basic Movement Ai----//
}

int Ai::Fall(Mobs* mobs[], int i, Tile* tiles[])
{
    return mobs[i]->getMobBox().y;
}

void Ai::Debug()
{
    cout << "Debug!" << endl;
}
