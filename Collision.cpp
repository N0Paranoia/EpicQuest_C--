#include "Collision.h"

Collision::Collision()
{
    //ctor
}

Collision::~Collision()
{
    //dtor
}

bool Collision::Check(SDL_Rect a, SDL_Rect b)
{
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if(bottomA <= topB)
    {
        return false;
    }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool Collision::CheckCloud(SDL_Rect a, SDL_Rect b)
{
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y + a.h - GRAVITY;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + GRAVITY;

    if(bottomA <= topB)
    {
        return false;
    }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool Collision::Check_Slope_45_Right(SDL_Rect a, SDL_Rect b)
{
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//[\]
    	if(bottomA <= (leftA % TILE_SIZE) + topB)
    	{
		return false;
    	}
	if(topA >= bottomB)
	{
		return false;
	}
	if(rightA <= leftB)
	{
		return false;
	}
	if(leftA >= rightB)
	{
		return false;
	}
	return true;
}

bool Collision::Check_Slope_45_Left(SDL_Rect a, SDL_Rect b)
{
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//[/]
    	if(bottomA <= (TILE_SIZE - (leftA % TILE_SIZE) + topB))
    	{
	       	return false;
    	}
	if(topA >= bottomB)
	{
		return false;
	}
	if(rightA <= leftB)
	{
		return false;
	}
	if(leftA >= rightB)
	{
	        return false;
	}
	return true;
}

bool Collision::Var(SDL_Rect cBox, Tile* tiles[], int type)
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == type)
        {
            if(this->Check(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::Wall(SDL_Rect cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_WALL)
        {
            if(this->Check(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::Cloud(SDL_Rect cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_LADDER_TOP || tiles[i]->getType() == TILE_PLATFORM)
        {
            if(this->CheckCloud(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::Slope_45_Right(SDL_Rect cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_SLOPE_RIGHT)
        {
            if(this->Check_Slope_45_Right(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::Slope_45_Left(SDL_Rect cBox, Tile* tiles[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(tiles[i]->getType() == TILE_SLOPE_LEFT)
        {
            if(this->Check_Slope_45_Left(cBox, tiles[i]->getTileBox()))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::Stick(SDL_Rect cBox, Tile* tiles[])
{
	for(int i = 0; i < TOTAL_TILES; i++)
	{
        	if(tiles[i]->getType() == TILE_WALL || 
			tiles[i]->getType() == TILE_LADDER_TOP || 
			tiles[i]->getType() == TILE_PLATFORM)
        	{
			if(this->Check(cBox, tiles[i]->getTileBox()))
			{
                		return true;
            		}
		}
        	else if(tiles[i]->getType() == TILE_SLOPE_LEFT)
		{
        		if(this->Check_Slope_45_Left(cBox, tiles[i]->getTileBox()))
        		{
               			return true;
        		}
		}
		else if(tiles[i]->getType() == TILE_SLOPE_RIGHT)
		{
        		if(this->Check_Slope_45_Right(cBox, tiles[i]->getTileBox()))
        		{
               			return true;
        		}
		}	
    	}
    	return false;
}
