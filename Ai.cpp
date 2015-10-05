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

int Ai::Move(Mobs* mobs[], int i)
{
        return mobs[i]->getMobBox().x +4;
}
