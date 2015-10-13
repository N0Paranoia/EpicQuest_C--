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
    cout << i << endl;
    cout << "Left[" << i << "] = " << Left[i] << endl;
    cout << "Right[" << i << "] = " << Right[i] << endl;
    // Left[64] = true;
    // Right[64] = false;
    // Left[85] = false;
    // Right[85] = true;
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
        else
        {
            Left[i] = true;
            Right[i] = false;
        }
    }
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
}

int Ai::Fall(Mobs* mobs[], int i, Tile* tiles[])
{
    return mobs[i]->getMobBox().y;
}
