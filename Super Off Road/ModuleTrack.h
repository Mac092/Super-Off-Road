#ifndef __MODULETRACK_H__
#define __MODULETRACK_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include <vector>

struct SDL_Texture;

class TerrainAlteration;

class ModuleTrack :
	public Module
{
public:
	ModuleTrack(bool start_enabled = true);
	~ModuleTrack();

	bool Start();
	update_status Update();
	bool CleanUp();
	void evaluateHeightMap();

	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect wall;
	SDL_Rect poodle1Rect;
	vector<TerrainAlteration*> terrainAlterations; 
	int heightmap[SCREEN_WIDTH][SCREEN_HEIGHT];
	int checkHeightSpecificValue(Uint32 pixel);
	

	TerrainAlteration * poodle1 = nullptr;

};

#endif // __MODULETRACK_H__