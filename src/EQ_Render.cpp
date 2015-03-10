#include "EQ.h"
#include "Constants.h"
#include "Player.h"

void EQ::Render()
{
    //Set Default color
    SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    //Clear screen
    SDL_RenderClear( Renderer );
    //Render Texture to screen
    SDL_RenderCopy(Renderer, Texture, NULL, NULL);

    //Render red filled quad
    SDL_Rect fillRect = { WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
    SDL_SetRenderDrawColor( Renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( Renderer, &fillRect );

    //Update screen
    SDL_RenderPresent( Renderer );
}


