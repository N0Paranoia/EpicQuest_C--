#include "EQ.h"
#include "Constants.h"

EQ::EQ()
{

}

int EQ::Execute()
{
    if(Init() == false)
    {
        return -1;
    }
    if(LoadMedia() == false)
    {
        return -1;
    }
    SDL_Event event;

    while(Running)
    {
        Fps();
        while(SDL_PollEvent(&event))
        {
            Event(&event);
        }
        Loop();
        Render();
    }
    Cleanup();
    return 0;
}

int main(int argc, char* argv[])
{
    EQ EpicQuest;
    return EpicQuest.Execute();
}
