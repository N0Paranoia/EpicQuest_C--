#include "Ai.h"
#include "Constants.h"
#include "Collision.h"

Ai::Ai()
{
    Left[1] = false;
    Right[1] = false;
}

Ai::~Ai()
{
    //dtor
}

int Ai::Move(Mobs* mobs[])
{
    for(int i = 0; i < 2; i++)
    {
        return mobs[i]->getMobBox().x + 1;
    }
}
