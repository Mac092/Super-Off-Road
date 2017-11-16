#include "Application.h"
#include "ModuleTrack.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"



ModuleTrack::ModuleTrack(bool start_enabled) : Module(start_enabled)
{
	//truck terrain
	ground.x = 8;
	ground.y = 1408;
	ground.h = 198;
	ground.w = 319;

	//walls
	wall.x = 336;
	wall.y = 1408;
	wall.h = 198;
	wall.w = 319;
}


ModuleTrack::~ModuleTrack()
{
}

bool ModuleTrack::Start()
{
	LOG("Loading Current Track");
	
	graphics = App->textures->Load("Game/stages.png");
	App->audio->PlayMusic("Game/Off-Road_Fandango.wav", 0);

	App->player->Init();
	App->player->Start();

	return true;
}

update_status ModuleTrack::Update()
{
	App->renderer->Blit(graphics, 10, 10, &ground, 3.0f);
	App->renderer->Blit(graphics, 38, 10, &wall, 3.0f);
	App->player->Update();

	return UPDATE_CONTINUE;
}

bool ModuleTrack::CleanUp()
{
	return false;
}
