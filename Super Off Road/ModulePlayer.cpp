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
	setUpCarFrames();

	graphics = App->textures->Load("Game/red_sprites.png"); // arcade version
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
	SDL_Rect frame;

	carFrames->push_back(currentFrame);
	
	frame = buildNewSprite(411,11,15,10);
	carFrames->push_back(frame);
	frame = buildNewSprite(435,10,14,11);
	carFrames->push_back(frame);
	frame = buildNewSprite(459, 10, 15, 11);
	carFrames->push_back(frame);
	frame = buildNewSprite(483, 9, 15, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(507, 8, 15, 13);
	carFrames->push_back(frame);
	frame = buildNewSprite(531, 8, 13, 13);
	carFrames->push_back(frame);
	frame = buildNewSprite(555, 8, 13, 13);
	carFrames->push_back(frame);
	frame = buildNewSprite(579, 8, 12, 13);
	carFrames->push_back(frame);
	frame = buildNewSprite(603, 8, 10, 13);
	carFrames->push_back(frame);
	frame = buildNewSprite(627, 8, 8, 13);
	carFrames->push_back(frame);
	frame = buildNewSprite(643, 9, 10, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(667, 9, 13, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(691, 9, 14, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(715, 10, 15, 11);
	carFrames->push_back(frame);
	frame = buildNewSprite(739,11, 16, 10);
	carFrames->push_back(frame);
	frame = buildNewSprite(11, 12, 15, 9);
	carFrames->push_back(frame);
	frame = buildNewSprite(35, 12, 16, 9);
	carFrames->push_back(frame);
	frame = buildNewSprite(59, 11, 16, 10);
	carFrames->push_back(frame);
	frame = buildNewSprite(83, 10, 17, 11);
	carFrames->push_back(frame);
	frame = buildNewSprite(107, 10, 16, 11);
	carFrames->push_back(frame);
	frame = buildNewSprite(131, 9, 15, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(155, 9, 14, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(179, 9, 14, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(203, 9, 12, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(227, 9, 10, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(251, 9, 9, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(267, 9, 10, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(291, 9, 12, 12);
	carFrames->push_back(frame);
	frame = buildNewSprite(315, 10, 14, 11);
	carFrames->push_back(frame);
	frame = buildNewSprite(339, 11, 15, 10);
	carFrames->push_back(frame);
	frame = buildNewSprite(363, 12, 16, 9);
	carFrames->push_back(frame);
	

}

Orientation ModulePlayer::getCarOrientation()
{
	return carOrientation;
}

SDL_Rect ModulePlayer::buildNewSprite(int x, int y, int w, int h) {

	SDL_Rect sprite;
	sprite.x = x;
	sprite.y = y;
	sprite.w = w;
	sprite.h = h;
	
	return sprite;
}

// Update
update_status ModulePlayer::Update()
{


	/*if (App->input->GetKey(SDLK_RIGHT) == KEY_DOWN) {
		if (currentSpritePosition != carFrames->size() - 1) {
			currentSpritePosition += 1;
			currentFrame = carFrames->at(currentSpritePosition);
		}
		else {
			currentSpritePosition = 0;
			currentFrame = carFrames->at(currentSpritePosition);
			
		}
		
	}
	else if (App->input->GetKey(SDLK_LEFT) == KEY_DOWN) {
		if (currentSpritePosition == 0) {
			currentFrame = carFrames->back();
			currentSpritePosition = carFrames->size()-1;
		}
		else {
			currentFrame = carFrames->at(currentSpritePosition - 1);
			currentSpritePosition -= 1;
		}
	}*/

	if (gameSpeed % 10 == 0) {


		//Check and apply if it's necessary direction changes and skid consequences
		if (App->input->GetKey(SDLK_RIGHT) == KEY_REPEAT) {
			
			//Control skidPower
			if (skidPower < SKID_LEVEL_4) {
				skidPower++;
			}
			else {
				skidPower = 1;
			}

			skidEffect(false);
		}else if (App->input->GetKey(SDLK_LEFT) == KEY_REPEAT) {

			//Control skidPower
			if (skidPower < SKID_LEVEL_4) {
				skidPower++;
			}
			else {
				skidPower = 1;
			}

			skidEffect(true);
		}
		else if (App->input->GetKey(SDLK_RIGHT) == KEY_UP || App->input->GetKey(SDLK_LEFT) == KEY_UP) {
			skidPower = 0;
		}



		//Apply acceleration or deaccelaration depending on the current situation
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			if (carCurrentSpeed < carProperties.maxSpeed) {
				carCurrentSpeed ++;
			}

		}
		else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
			if (carCurrentSpeed < carProperties.maxSpeed) {
				carCurrentSpeed ++ ;
			}
		}
		else {
			if (carCurrentSpeed > 0) {
				carCurrentSpeed--;
			}
		}

		//Car movement
		if (carOrientation == NORTH) {
			carPosition.y -= carCurrentSpeed;
		}
		else if (carOrientation == SOUTH) {
			carPosition.y += carCurrentSpeed;
		}
		else if (carOrientation == EAST) {
			carPosition.x += carCurrentSpeed;
		}
		else {
			carPosition.x -= carCurrentSpeed;
		}
	}
	


	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
		carPosition.x--;
	}else if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
		carPosition.x++;
	}
	else if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
		carPosition.y--;
	}
	else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		carPosition.y++;
	}
	else if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		carPosition.y++;
		carPosition.x--;
	}
	else if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
		carPosition.y--;
		carPosition.x--;
	}
	else if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
		carPosition.y--;
		carPosition.x++;
	}
	else if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
		carPosition.y++;
		carPosition.x++;
	}
	App->renderer->Blit(graphics, carPosition.x, carPosition.y, &currentFrame, 3.0f);

	gameSpeed++;
	return UPDATE_CONTINUE;
}

void ModulePlayer::skidEffect(const bool skidToTheLeft) {

	//Skid Power evaluation
	if (skidPower == SKID_LEVEL_1) {
		carCurrentSpeed = (carCurrentSpeed*95)/100;
		skidPenalty(skidToTheLeft,1);
	}
	else if (skidPower == SKID_LEVEL_2) {
		carCurrentSpeed = (carCurrentSpeed * 85) / 100;
		skidPenalty(skidToTheLeft, 2);
	}
	else if (skidPower == SKID_LEVEL_3) {
		carCurrentSpeed = (carCurrentSpeed * 70) / 100;
		skidPenalty(skidToTheLeft, 3);
	}
	else if (skidPower == SKID_LEVEL_4) {
		carCurrentSpeed = (carCurrentSpeed * 50) / 100;
		skidPenalty(skidToTheLeft, 4);
	}

}

void ModulePlayer::skidPenalty(const bool skidTotheLeft, const int skidLevel)
{
	int penalty = 0;
	if (skidLevel == SKID_LEVEL_1 || skidLevel == SKID_LEVEL_3) {
		penalty = 1;
	}
	else if (skidLevel == SKID_LEVEL_2) {
		penalty = 2;
	}

	switch (carOrientation) {
	case NORTH:
		if (skidTotheLeft) {
			carPosition.x -= penalty;

			if (currentSpritePosition != carFrames->size() - 1) {
			currentSpritePosition += 1;
			currentFrame = carFrames->at(currentSpritePosition);
			}
			else {
				currentSpritePosition = 0;
				currentFrame = carFrames->at(currentSpritePosition);
			}

			if (currentSpritePosition == 0) {
				carOrientation = WEST;
			}
		}
		else {
			carPosition.x += penalty;

			if (currentSpritePosition == 0) {
				currentFrame = carFrames->back();
				currentSpritePosition = carFrames->size() - 1;
			}
			else {
				currentFrame = carFrames->at(currentSpritePosition - 1);
				currentSpritePosition -= 1;
			}

			if (currentSpritePosition == 16) {
				carOrientation = EAST;
			}
			
		}
		break;
	case SOUTH:
		if (skidTotheLeft) {
			carPosition.x += penalty;

			if (currentSpritePosition == 0) {
				currentFrame = carFrames->back();
				currentSpritePosition = carFrames->size() - 1;
			}
			else {
				currentFrame = carFrames->at(currentSpritePosition - 1);
				currentSpritePosition -= 1;
			}

			if (currentSpritePosition == 0) {
				carOrientation = WEST;
			}

		}
		else {
			carPosition.x -= penalty;

			if (currentSpritePosition != carFrames->size() - 1) {
				currentSpritePosition += 1;
				currentFrame = carFrames->at(currentSpritePosition);
			}
			else {
				currentSpritePosition = 0;
				currentFrame = carFrames->at(currentSpritePosition);
			}

			if (currentSpritePosition == 16) {
				carOrientation = EAST;
			}

		}
		break;
	case WEST:
		if (skidTotheLeft) {
			carPosition.y -= penalty;

			if (currentSpritePosition != carFrames->size() - 1) {
				currentSpritePosition += 1;
				currentFrame = carFrames->at(currentSpritePosition);
			}
			else {
				currentSpritePosition = 0;
				currentFrame = carFrames->at(currentSpritePosition);
			}

			if (currentSpritePosition == 8) {
				carOrientation = SOUTH;
			}
		}
		else {
			carPosition.y += penalty;

			if (currentSpritePosition == 0) {
				currentFrame = carFrames->back();
				currentSpritePosition = carFrames->size() - 1;
			}
			else {
				currentFrame = carFrames->at(currentSpritePosition - 1);
				currentSpritePosition -= 1;
			}

			if (currentSpritePosition == 24) {
				carOrientation = NORTH;
			}
		}
		break;
	case EAST:
		if (skidTotheLeft) {
			carPosition.y += penalty;

			if (currentSpritePosition == 0) {
				currentFrame = carFrames->back();
				currentSpritePosition = carFrames->size() - 1;
			}
			else {
				currentFrame = carFrames->at(currentSpritePosition - 1);
				currentSpritePosition -= 1;
			}

			if (currentSpritePosition == 24) {
				carOrientation = NORTH;
			}
		}
		else {
			carPosition.y -= penalty;

			if (currentSpritePosition != carFrames->size() - 1) {
				currentSpritePosition += 1;
				currentFrame = carFrames->at(currentSpritePosition);
			}
			else {
				currentSpritePosition = 0;
				currentFrame = carFrames->at(currentSpritePosition);
			}

			if (currentSpritePosition == 8) {
				carOrientation = SOUTH;
			}

		}
		break;
	default:
		break;
	}
}

