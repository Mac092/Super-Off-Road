#include "TerrainAlteration.h"



TerrainAlteration::TerrainAlteration(int spriteX, int spriteY, int spriteW, int spriteH)
{
	type = TERRAIN_ALTERATION;
}

TerrainAlteration::~TerrainAlteration()
{
}



bool TerrainAlteration::checkCollisionWithExternalCollider(int carPlayerRadius, iPoint carCenterPoint)
{
	return false;
}

