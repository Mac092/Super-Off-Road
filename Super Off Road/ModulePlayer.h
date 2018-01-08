#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include <vector>
#include <map>

# define RADIUS_CAR_COLLIDER 10
struct SDL_Texture;

enum Orientation {NORTH, SOUTH, EAST, WEST, NORTHWEST, SOUTHWEST, NORTHEAST, SOUTHEAST};

struct CarPowerUps {
	int maxSpeed = 6;
	//int tires
	//int amountOfNitro
	//int shock
	int maxAccel = 0;

};

struct CarMovement {
	std::vector<Orientation> currentCarOrientation;
	std::vector < std::vector<SDL_Rect>>* rotationSpritesFromTerrainAlteration;
	SDL_Rect currentCarSprite;
	bool orientationChanged;
	bool isRotatedDueTerrainAlteration = false;
	int carOrientationPosition;
	int currentCarSpeed = 0;
	int currentCarAccel = 0;

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
	vector<vector<SDL_Rect>>* setUpCarRotationFrames(CarMovement* frameCar, int framePosition);
	void setUpCarEngine();
	iPoint getCarCenterPosition() const;
	SDL_Rect buildNewSprite(int x, int y, int w, int h);
	//Orientation getCarOrientation();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* rotatedGraphicsDueTerrainAlteration = nullptr;
	SDL_Rect currentFrame;
	iPoint carPosition;
	int currentFramePosition = 0;
	std::vector<CarMovement> carFrames;

	void rotateCarSprite(string side);
	void skidEffect(const bool skidToTheLeft);
	void skidPenalty(const bool skidTotheLeft, const int skidLevel);
	void moveCar();


	CarPowerUps carPowerUps;
	CarMovement currentCarMovement;
	
	bool accelerated = false;
	bool maxSpeedReached = false;
	int gameSpeed = 0;
	int skidPower = 0;
	int skidLevel = 0;
	bool skidToTheLeft = false;
	int gameRotation = 1;

};

#endif // __MODULEPLAYER_H__