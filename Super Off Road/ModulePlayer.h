#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include <vector>



struct SDL_Texture;

enum Orientation {NORTH, SOUTH, EAST, WEST};


struct CarProperties {
	int maxSpeed = 20;
	//int tires
	//int amountOfNitro
	//int shock
	//int accel
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	void skidEffect(const bool skidToTheLeft);
	void skidPenalty(const bool skidTotheLeft, const int skidLevel);
	bool CleanUp();
	void setUpCarFrames();
	Orientation getCarOrientation();

	SDL_Rect buildNewSprite(int x, int y, int w, int h);

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect currentFrame;
	iPoint carPosition;
	int currentSpritePosition = 0;
	vector<SDL_Rect> carFrames[32];
	Orientation carOrientation = WEST;
	int carCurrentSpeed = 0;
	CarProperties carProperties;

	int gameSpeed = 0;
	int skidPower = 0;

};

#endif // __MODULEPLAYER_H__