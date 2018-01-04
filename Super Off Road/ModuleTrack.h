#ifndef __MODULETRACK_H__
#define __MODULETRACK_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;


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

	int heightmap[SCREEN_WIDTH][SCREEN_HEIGHT];
	int checkHeightSpecificValue(Uint32 pixel);
	

};

#endif // __MODULETRACK_H__