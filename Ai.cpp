#include "Ai.h"
#include "Constants.h"

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
    return Left[1];
}
