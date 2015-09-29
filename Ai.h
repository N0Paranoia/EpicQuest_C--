#ifndef AI_H
#define AI_H

#include <SDL.h>
#include "Mobs.h"

class Ai
{
    public:
        Ai();
        virtual ~Ai();
        int Move(Mobs* mobs[]);
    protected:
    private:
    public:
        bool Left[2];
        bool Right[2];
};

#endif // AI_H
