
#include "Application.h"
#include "ModuleTrack.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "TerrainAlteration.h"

#include "SDL_image\include\SDL_image.h"



ModuleTrack::ModuleTrack(bool start_enabled) : Module(start_enabled)
{
	//truck terrain
	ground.x = 0;
	ground.y = 0;
	ground.h = 192;
	ground.w = 320;

	//walls
	/*wall.x = 336;
	wall.y = 1408;
	wall.h = 198;
	wall.w = 319;*/



}


ModuleTrack::~ModuleTrack()
{
	terrainAlterations.push_back(poodle1 = new TerrainAlteration(poodle1Rect.x,poodle1Rect.y,poodle1Rect.w,poodle1Rect.h));
	 
}

bool ModuleTrack::Start()
{
	LOG("Loading Current Track");
	
	graphics = App->textures->Load("Game/stage.png");
	App->audio->PlayMusic("Game/Off-Road_Fandango.wav", 0);

	App->player->Init();
	App->player->Start();

	evaluateHeightMap();

	return true;
}

update_status ModuleTrack::Update()
{
	App->renderer->Blit(graphics, 0, 0, &ground, 3.0f);
	//App->renderer->Blit(graphics, 38, 10, &wall, 3.0f);
	App->player->Update();
	

	return UPDATE_CONTINUE;
}

bool ModuleTrack::CleanUp()
{
	return false;
}

void ModuleTrack::evaluateHeightMap()
{
	// load height map png into image
	SDL_Surface *image;
	image = IMG_Load("Game/first_stage.bmp");
	if (!image) {
		printf("IMG_Load: %s\n", IMG_GetError());
		// handle error
	}

	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)image->pixels;

	SDL_LockSurface(image);

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			Uint32 pixel = pixels[(j * image->w) + i];
			heightmap[i][j] = checkHeightSpecificValue(pixel);
		}
	}


	SDL_UnlockSurface(image);
}


int ModuleTrack::checkHeightSpecificValue(Uint32 pixel)
{
	Uint8 *colors = (Uint8*)&pixel;
	int red = colors[0];
	int green = colors[1];
	int blue = colors[2];
	
	if ((red & green & blue) == 50) {
		return 5;
	}
	else if ((red & green & blue) == 100) {
		return 4;
	}
	else if ((red & green & blue) == 150) {
		return 3;
	}
	else if ((red & green & blue) == 200) {
		return 2;
	}
	else if ((red & green & blue) == 250) { // poodle
		return 20;
	}
	else if ((red & green & blue) == 0) { // fence
		return 10;

	}
	else {
		return 0;
	}
}
