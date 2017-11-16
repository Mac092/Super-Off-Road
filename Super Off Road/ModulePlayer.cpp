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
		}
		else {
			carPosition.x += penalty;
		}
		break;
	case SOUTH:
		if (skidTotheLeft) {
			carPosition.x += penalty;
		}
		else {
			carPosition.x -= penalty;
		}
		break;
	case WEST:
		if (skidTotheLeft) {
			carPosition.y -= penalty;
		}
		else {
			carPosition.y += penalty;
		}
		break;
	case EAST:
		if (skidTotheLeft) {
			carPosition.y += penalty;
		}
		else {
			carPosition.y -= penalty;
		}
		break;
	default:
		break;
	}
}

