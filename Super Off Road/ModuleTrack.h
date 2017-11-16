#ifndef __MODULETRACK_H__
#define __MODULETRACK_H__

#include "Module.h"
#include "Animation.h"
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


	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect wall;

};

#endif // __MODULETRACK_H__