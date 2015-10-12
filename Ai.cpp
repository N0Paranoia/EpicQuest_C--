#include "Ai.h"
#include "Constants.h"
#include "Collision.h"

Collision aiCollision;

Ai::Ai()
{

}

Ai::~Ai()
{
    //dtor
}

int Ai::Move(Mobs* mobs[], int i, Tile* tiles[])
{
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
    if(Right[i])
    {
        return mobs[i]->getMobBox().x +4;
    }
    if(Left[i])
    {
        return mobs[i]->getMobBox().x -4;
    }
    return 0;
}

int Ai::Fall(Mobs* mobs[], int i, Tile* tiles[])
{
    return mobs[i]->getMobBox().y+ GRAVITY;
}
