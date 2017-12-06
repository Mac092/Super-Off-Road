#ifndef __TERRRAINALTERATION_H__
#define __TERRRAINALTERATION_H__

#include "SDL\include\SDL.h"
#include "Point.h"
#include <string>

enum AlterationType { FENCE, PUDDLE, BUMP, RAMP, TERRAIN_ALTERATION };

class TerrainAlteration
{

public:
	TerrainAlteration(int spriteX, int spriteY, int spriteW, int spriteH);
	~TerrainAlteration();
	
	bool checkCollisionWithExternalCollider(int carPlayerRadius, iPoint carCenterPoint);
	//virtual bool checkCollisionWithOwnCollider(const SDL_Rect carsActualRectangle);
	SDL_Rect externalCollider;
	
	AlterationType type;
};

extern TerrainAlteration* terrain;


#endif