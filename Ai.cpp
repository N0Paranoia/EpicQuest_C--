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
    if(aiCollision.Ai(mobs, tiles))
    {
        cout << "test" << endl;
    }
    if(mobs[i]->getMobBox().x >= 480)
    {
        Right[i] = false;
        Left[i] = true;
    }
    else if(mobs[i]->getMobBox().x <= 0)
    {
        Left[i] = false;
        Right[i] = true;
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
