#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{

	// idle
	currentFrame.x = 388;
	currentFrame.y = 12;
	currentFrame.h = 9;
	currentFrame.w =  15;

	gameSpeed = 0;

	
}

ModulePlayer::~ModulePlayer()
{
	//Check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	carPosition.x = 165;
	carPosition.y = 168;
	currentCarMovement.orientationChanged = false;
	currentCarMovement.carOrientationPosition = 0;

	setUpCarFrames();
	setUpCarEngine();
	
	graphics = App->textures->Load("Game/red_sprites.png");
	rotatedGraphicsDueTerrainAlteration = App->textures->Load("Game/rotatedSpritesDueTerrainAlteration.png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

void ModulePlayer::setUpCarFrames()
{
	vector<Orientation> frameMovement = {WEST,WEST,WEST,WEST,WEST,WEST,WEST };

	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);
	
	frameMovement = { WEST,WEST,WEST,SOUTHWEST,WEST,WEST,WEST };
	currentFrame = buildNewSprite(411,11,15,10);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { WEST,WEST,SOUTHWEST,WEST,WEST,WEST,SOUTHWEST };
	currentFrame = buildNewSprite(435, 10, 14, 11);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { WEST,SOUTHWEST,WEST,SOUTHWEST,WEST,SOUTHWEST,WEST };
	currentFrame = buildNewSprite(459, 10, 15, 11);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { SOUTHWEST,SOUTHWEST,SOUTHWEST,SOUTHWEST,SOUTHWEST,SOUTHWEST,SOUTHWEST };
	currentFrame = buildNewSprite(483, 9, 15, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { SOUTH,SOUTHWEST,SOUTH,SOUTHWEST,SOUTH,SOUTHWEST,SOUTH };
	currentFrame = buildNewSprite(507, 8, 15, 13);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { SOUTH,SOUTH,SOUTHWEST,SOUTH,SOUTH,SOUTHWEST,SOUTH };
	currentFrame = buildNewSprite(531, 8, 13, 13);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);
	
	frameMovement = { SOUTH,SOUTH,SOUTH,SOUTHWEST,SOUTH,SOUTH,SOUTH };
	currentFrame = buildNewSprite(555, 8, 13, 13);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { SOUTH,SOUTH,SOUTH,SOUTH,SOUTH,SOUTH,SOUTH };
	currentFrame = buildNewSprite(579, 8, 12, 13);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { SOUTH,SOUTH,SOUTH,SOUTH,SOUTH,SOUTH,SOUTH };
	currentFrame = buildNewSprite(603, 8, 10, 13);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { SOUTH,SOUTH,SOUTH,SOUTHEAST,SOUTH,SOUTH,SOUTH };
	currentFrame = buildNewSprite(627, 8, 8, 13);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { SOUTH,SOUTHEAST,SOUTH,SOUTHEAST,SOUTH,SOUTHEAST,SOUTH };
	currentFrame = buildNewSprite(643, 9, 10, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { SOUTHEAST,SOUTHEAST,SOUTHEAST,SOUTHEAST,SOUTHEAST,SOUTHEAST,SOUTHEAST };
	currentFrame = buildNewSprite(667, 9, 13, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);
	
	frameMovement = { EAST,SOUTHEAST,EAST,SOUTHEAST,EAST,SOUTHEAST,EAST };
	currentFrame = buildNewSprite(691, 9, 14, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { EAST,EAST,SOUTHEAST,EAST,EAST,SOUTHEAST,EAST };
	currentFrame = buildNewSprite(715, 10, 15, 11);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { EAST,EAST,EAST,SOUTHEAST,EAST,EAST,EAST };
	currentFrame = buildNewSprite(739, 11, 16, 10);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { EAST,EAST,EAST,EAST,EAST,EAST,EAST };
	currentCarMovement.rotationSpritesFromTerrainAlteration = setUpCarRotationFrames(&currentCarMovement,16);
	currentFrame = buildNewSprite(11, 12, 15, 9);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { EAST,EAST,EAST,NORTHEAST,EAST,EAST,EAST };
	currentFrame = buildNewSprite(35, 12, 16, 9);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { EAST,EAST,NORTHEAST,EAST,EAST,NORTHEAST,EAST };
	currentFrame = buildNewSprite(59, 11, 16, 10);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { EAST,NORTHEAST,EAST,NORTHEAST,EAST,NORTHEAST,EAST };
	currentFrame = buildNewSprite(83, 10, 17, 11);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { NORTHEAST,NORTHEAST,NORTHEAST,NORTHEAST,NORTHEAST,NORTHEAST,NORTHEAST };
	currentFrame = buildNewSprite(107, 10, 16, 11);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { NORTH,NORTHEAST,NORTH,NORTHEAST,NORTH,NORTHEAST,NORTH };
	currentFrame = buildNewSprite(131, 9, 15, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { NORTH,NORTH,NORTHEAST,NORTH,NORTH,NORTHEAST,NORTH };
	currentFrame = buildNewSprite(155, 9, 14, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { NORTH,NORTH,NORTH,NORTHEAST,NORTH,NORTH,NORTH };
	currentFrame = buildNewSprite(179, 9, 14, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { NORTH,NORTH,NORTH,NORTH,NORTH,NORTH,NORTH };
	currentFrame = buildNewSprite(203, 9, 12, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { NORTH,NORTH,NORTH,NORTHWEST,NORTH,NORTH,NORTH };
	currentFrame = buildNewSprite(227, 9, 10, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { NORTH,NORTH,NORTHWEST,NORTH,NORTH,NORTHWEST,NORTH };
	currentFrame = buildNewSprite(251, 9, 9, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { NORTH,NORTHWEST,NORTH,NORTHWEST,NORTH,NORTHWEST,NORTH };
	currentFrame = buildNewSprite(267, 9, 10, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { NORTHWEST,NORTHWEST,NORTHWEST,NORTHWEST,NORTHWEST,NORTHWEST,NORTHWEST };
	currentFrame = buildNewSprite(291, 9, 12, 12);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	frameMovement = { WEST,NORTHWEST,WEST,NORTHWEST,WEST,NORTHWEST,WEST };
	currentFrame = buildNewSprite(315, 10, 14, 11);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);


	frameMovement = { WEST,WEST,NORTHWEST,WEST,WEST,NORTHWEST,WEST };
	currentFrame = buildNewSprite(339, 11, 15, 10);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);


	frameMovement = { WEST,WEST,WEST,NORTHWEST,WEST,WEST,WEST };
	currentFrame = buildNewSprite(363, 12, 16, 9);
	currentCarMovement.currentCarOrientation = frameMovement;
	currentCarMovement.currentCarSprite = currentFrame;
	carFrames.push_back(currentCarMovement);

	currentFrame = carFrames.at(0).currentCarSprite;
	
}

vector<vector<SDL_Rect>>* ModulePlayer::setUpCarRotationFrames(CarMovement* frameCar, int framePosition)
{
	vector<vector<SDL_Rect>> rotationFrames(9,vector<SDL_Rect>(9)) ;
	//SDL_Rect* rotationFrames = new SDL_Rect[9 * 9];
	//// declaration
	//char *dog = new char[640 * 480];

	//// usage
	//dog[first_index * 640 + second_index] = 'a';

	//// deletion
	//delete[] dog;

	SDL_Rect frameToAdd;
	switch (framePosition) {
	case 16:
		rotationFrames[0][0] = frameCar->currentCarSprite;
		frameToAdd = buildNewSprite(33,8,15,15);
		rotationFrames[0][1] = frameToAdd;
		frameToAdd = buildNewSprite(57,7,16,8);
		rotationFrames[0][2] = frameToAdd;
		frameToAdd = buildNewSprite(81,7,13,8);
		rotationFrames[0][3] = frameToAdd;
		frameToAdd = buildNewSprite(101, 6, 14, 9);
		rotationFrames[0][4] = frameToAdd;
		frameToAdd = buildNewSprite(57, 7, 16, 8);

	default:
		break;
	}

	return &rotationFrames;
}

void ModulePlayer::setUpCarEngine()
{
	switch (carPowerUps.maxSpeed) {
		case(0):
		case(1):
		case(2):
			currentCarMovement.currentCarSpeed = 3;
			break;
		case(3):
		case(4):
		case(5):
			currentCarMovement.currentCarSpeed = 2;
			break;
		case(6):
			currentCarMovement.currentCarSpeed = 1;
			break;
		
	}
	switch (carPowerUps.maxAccel) {
		case(0):
		case(1):
			currentCarMovement.currentCarAccel = 8;
			break;
		case(2):
		case(3):
			currentCarMovement.currentCarAccel = 7;
			break;
		case(4):
		case(5):
			currentCarMovement.currentCarAccel = 6;
			break;
		case(6):
			currentCarMovement.currentCarAccel = 5;
			break;
	}
}

//TODO crear clase círculo y sustituirlo por el iPoint para no malgastar w y h que no se usan
iPoint ModulePlayer::getCarCenterPosition() const
{
	iPoint carCenterPosition;

	carCenterPosition.x = carPosition.x + currentFrame.w/2;
	carCenterPosition.y = carPosition.y + currentFrame.h/2;

	return carCenterPosition;
}


SDL_Rect ModulePlayer::buildNewSprite(int x, int y, int w, int h) {

	SDL_Rect sprite;
	sprite.x = x;
	sprite.y = y;
	sprite.w = w;
	sprite.h = h;
	
	return sprite;
}

void ModulePlayer::rotateCarSprite(string side)
{
	if (side == "LEFT") {
		if (currentFramePosition == carFrames.size() - 1) {
			currentFramePosition = 0;
		}
		else {
			currentFramePosition += 1;
		}
		currentFrame = carFrames.at(currentFramePosition).currentCarSprite;
	}
	else if(side == "RIGHT"){
		if (currentFramePosition == 0) {
			currentFramePosition = carFrames.size() - 1;
		}
		else {
			currentFramePosition -= 1;
		}
		currentFrame = carFrames.at(currentFramePosition).currentCarSprite;
	}
}



void ModulePlayer::moveCar()
{
	//Car movement
	if (carFrames.at(currentFramePosition).currentCarOrientation.at(currentCarMovement.carOrientationPosition) == NORTH) {
		carPosition.y -= 2;
	}
	else if (carFrames.at(currentFramePosition).currentCarOrientation.at(currentCarMovement.carOrientationPosition) == SOUTH) {
		carPosition.y += 2;
	}
	else if (carFrames.at(currentFramePosition).currentCarOrientation.at(currentCarMovement.carOrientationPosition) == EAST) {
		carPosition.x += 2;
	}
	else if(carFrames.at(currentFramePosition).currentCarOrientation.at(currentCarMovement.carOrientationPosition) == WEST) {
		carPosition.x -= 2;
	}
	else if (carFrames.at(currentFramePosition).currentCarOrientation.at(currentCarMovement.carOrientationPosition) == SOUTHWEST) {
		carPosition.y += 1;
		carPosition.x -= 1;
	}
	else if (carFrames.at(currentFramePosition).currentCarOrientation.at(currentCarMovement.carOrientationPosition) == SOUTHEAST) {
		carPosition.y += 1;
		carPosition.x += 1;
	}
	else if (carFrames.at(currentFramePosition).currentCarOrientation.at(currentCarMovement.carOrientationPosition) == NORTHEAST) {
		carPosition.y -= 1;
		carPosition.x += 1;
	}
	else if (carFrames.at(currentFramePosition).currentCarOrientation.at(currentCarMovement.carOrientationPosition) == NORTHWEST) {
		carPosition.y -= 1;
		carPosition.x -= 1;
	}
	// iterate over sprites of same animation when player doesn't change orientation or direction
	if (currentCarMovement.carOrientationPosition < 6) {
		currentCarMovement.carOrientationPosition += 1;
	}
	else {
		currentCarMovement.carOrientationPosition = 0;
	}
}


// Update
update_status ModulePlayer::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
		accelerated = true;
		if (currentCarMovement.currentCarAccel != currentCarMovement.currentCarSpeed) {
			//moving until reach max speed
			if (currentCarMovement.currentCarAccel == gameSpeed) {
				moveCar();
				currentCarMovement.currentCarAccel -= 1;
				gameSpeed = 0;
			}
			else {
				gameSpeed++;
			}
		}
		else {
			if (currentCarMovement.currentCarSpeed == gameSpeed) {
				//TODO si se aplica un nitro se realizará el moveCar varias veces de forma extra durante unos frames
				moveCar();
				gameSpeed = 0;
			}
			else {
				gameSpeed++;
			}
		}

	}

//if (gameSpeed % 6 == 0) {

//	//----- Car Moving logic
//	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {	
//			moveCar();
//	}
//	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
//		if (carCurrentSpeed < carProperties.maxSpeed) {
//				carCurrentSpeed++;
//			}
//		for (int i = 0; i < carCurrentSpeed; i++) {
//			moveCar();
//			App->renderer->Blit(graphics, carPosition.x, carPosition.y, &currentFrame, 3.0f);
//		}
//		
//		
//	}
//	else {
//		// ---- Car deacceleration logic
//		//TODO: No me gusta esta comprobación pues se está ejecutando todo el rato...
//		if (carCurrentSpeed > 0) {
//			carCurrentSpeed--;
//			moveCar();
//		}
//	}
//	
//}

if (gameRotation == currentCarMovement.currentCarSpeed + 3) {
	gameRotation = 1;
	
	//	else
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {

		rotateCarSprite("RIGHT");
		//		//Control skidPower
		//		if (skidLevel < SKID_LEVEL_7) {
		//			skidLevel++;
		//			skidPower++;
		//		}
		//		else {
		//			skidLevel = 0;
		//		}

		//		skidEffect(skidToTheLeft);

	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {

		rotateCarSprite("LEFT");
		//		//Control skidPower
		//		if (skidPower <= SKID_LEVEL_7) {
		//			skidLevel++;
		//			skidPower++;
		//		}
		//		else {
		//			skidLevel = 0;
		//		}
		//		skidToTheLeft = true;
		//		skidEffect(skidToTheLeft);
		//	}
		//	/*else if (App->input->GetKey(SDLK_RIGHT) == KEY_UP || App->input->GetKey(SDLK_LEFT) == KEY_UP) {
		//	skidPower--;
	}


	//	//TODO: No me gusta esta comprobación pues se está ejecutando todo el rato...
	//	if (skidPower > 0) {
	//		skidPower--;
	//		skidEffect(skidToTheLeft);

	//	}
}

	
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
		moveCar();
	}
	//---- Car rotation logic
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
		rotateCarSprite("LEFT");
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
		rotateCarSprite("RIGHT");
	}
	
    gameRotation++;
	//TODO: si el jugador está quito esto puede aumentar cada frame hasta ser una burrada
	App->renderer->Blit((currentCarMovement.isRotatedDueTerrainAlteration == false) ? graphics : rotatedGraphicsDueTerrainAlteration, carPosition.x, carPosition.y, &currentFrame, 3.0f);

	return UPDATE_CONTINUE;
}




