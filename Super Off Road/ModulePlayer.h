#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include <vector>
#include <map>

struct SDL_Texture;

enum Orientation {NORTH, SOUTH, EAST, WEST, NORTHWEST, SOUTHWEST, NORTHEAST, SOUTHEAST};


struct CarProperties {
	int maxSpeed =5;
	//int tires
	//int amountOfNitro
	//int shock
	//int accel
};

struct CarMovement {
	std::vector<Orientation> currentCarOrientation;
	SDL_Rect currentCarSprite;
	bool orientationChanged;
	int carOrientationPosition;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	
	bool CleanUp();
	void setUpCarFrames();
	//Orientation getCarOrientation();

	SDL_Rect buildNewSprite(int x, int y, int w, int h);

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect currentFrame;
	iPoint carPosition;
	int currentFramePosition = 0;
	std::vector<CarMovement> carFrames;
	void rotateCarSprite(string side);

	void skidEffect(const bool skidToTheLeft);
	void skidPenalty(const bool skidTotheLeft, const int skidLevel);
	
	int carCurrentSpeed = 1;

	void moveCar();
	CarProperties carProperties;
	CarMovement currentCarMovement;


	int gameSpeed = 0;
	int skidPower = 0;
	bool skidToTheLeft = false;
	//Orientation carOrientation = WEST;
};

#endif // __MODULEPLAYER_H__