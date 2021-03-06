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

}


ModuleTrack::~ModuleTrack()
{
	 
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
	// The reason of the 4 on the h value is to give the screen the black bars both above and beneath the ground
	App->renderer->Blit(graphics, 0, 4, &ground, 3.0f);
	int  heapstatus;
	char *buffer;

	// Allocate and deallocate some memory  
	if ((buffer = (char *)malloc(100)) != NULL)
		free(buffer);

	// Check heap status  
	heapstatus = _heapchk();
	switch (heapstatus)
	{
	case _HEAPOK:
		printf(" OK - heap is fine\n");
		break;
	case _HEAPEMPTY:
		printf(" OK - heap is empty\n");
		break;
	case _HEAPBADBEGIN:
		printf("ERROR - bad start of heap\n");
		break;
	case _HEAPBADNODE:
		printf("ERROR - bad node in heap\n");
		break;
	}
	App->player->Update();
	

	return UPDATE_CONTINUE;
}

bool ModuleTrack::CleanUp()
{
	return true;
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
